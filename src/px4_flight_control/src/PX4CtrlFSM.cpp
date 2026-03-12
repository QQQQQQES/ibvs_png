#include "PX4CtrlFSM.h"
#include <uav_utils/converters.h>
#include <std_msgs/Float64.h>

using namespace std;
using namespace uav_utils;

PX4CtrlFSM::PX4CtrlFSM(Parameter_t &param_, LinearControl &controller_) : param(param_), controller(controller_) /*, thrust_curve(thrust_curve_)*/
{
	state = HOVER;
	hover_pose.setZero();

	// Initialize PNG guidance (AL controller outputs)
	al_angular_velocity_.setZero();
	al_thrust_value_ = 0.0;
	al_desired_acceleration_.setZero();
	al_control_received_ = false;
	al_acceleration_received_ = false;
	last_al_control_time_ = ros::Time(0);
}


void PX4CtrlFSM::process()
{

	ros::Time now_time = ros::Time::now();
	Controller_Output_t u;
	Desired_State_t des(odom_data);
	bool rotor_low_speed_during_land = false;

	// check_png_guidance_state();

	if (takeoff_land_data.triggered) 
    {
        takeoff_land_data.triggered = false; 

        if (takeoff_land_data.takeoff_land_cmd == 1) // TAKEOFF
        {
            takeoff_trigger_ = true; // 触发起飞逻辑
            ROS_INFO("Receive Takeoff Command!");
        }
        else if (takeoff_land_data.takeoff_land_cmd == 2) // LAND
        {
            land_trigger_ = true; // 触发降落逻辑
            ROS_INFO("Receive Land Command!");
        }
    }
	// STEP1: state machine runs  
	switch (state)
	{
	
		case HOVER:
		{
			if (takeoff_trigger_ && state_data.current_state.mode == mavros_msgs::State::MODE_PX4_OFFBOARD)
			{
				if (takeoff_land_data.takeoff_land_cmd == quadrotor_msgs::TakeoffLand::TAKEOFF)
				{
					if (toggle_arm_disarm(true))
					{
						state = TAKEOFF;
						controller.resetThrustMapping();
						set_start_pose_for_takeoff_land(odom_data);
						ROS_INFO("\033[32m[px4ctrl] HOVER --> TAKEOFF \033[32m");
					}
					
				}
			}
			else if (land_trigger_ && state_data.current_state.mode == mavros_msgs::State::MODE_PX4_OFFBOARD)
			{
				if (takeoff_land_data.takeoff_land_cmd == quadrotor_msgs::TakeoffLand::LAND)
				{
					state = LAND;
					set_start_pose_for_takeoff_land(odom_data);
					ROS_INFO("\033[32m[px4ctrl] HOVER --> LAND \033[32m");
				}
			}
			else if (cmd2_is_received(now_time))
			{
				if (state_data.current_state.mode == "OFFBOARD")
				{
					state = CMD_CTRL;
					// des = get_cmd_des();
					ROS_INFO("\033[32m[px4ctrl] AUTO_HOVER(L2) --> CMD_CTRL(L3)\033[32m");
				}
			}
			else
			{
				// set_hov_with_rc();
				des = get_hover_des();
				// cout << "des.p=" << des.p.transpose() << endl;
			}

			break;
		}

		case TAKEOFF:
		{
			takeoff_trigger_ = false;
			if ((now_time - takeoff_land.toggle_takeoff_land_time).toSec() < AutoTakeoffLand_t::MOTORS_SPEEDUP_TIME) // Wait for several seconds to warn prople.
			{
				des = get_rotor_speed_up_des(now_time);
			}
			else if (odom_data.p(2) >= (takeoff_land.start_pose(2) + param.takeoff_land.height)) // reach the desired height
			{
				state = HOVER;
				set_hov_with_odom();
				ROS_INFO("\033[32m[px4ctrl] TAKEOFF --> HOVER \033[32m");
			}
			else
			{
				des = get_takeoff_land_des(param.takeoff_land.speed);
			}

			break;
		}

		case LAND:
		{
			land_trigger_ = false;
			if (!get_landed())
			{
				des = get_takeoff_land_des(-param.takeoff_land.speed);
			}
			else
			{
				rotor_low_speed_during_land = true;

				static bool print_once_flag = true;
				if (print_once_flag)
				{
					ROS_INFO("\033[32m[px4ctrl] Wait for abount 10s to let the drone arm.\033[32m");
					print_once_flag = false;
				}

				if (extended_state_data.current_extended_state.landed_state == mavros_msgs::ExtendedState::LANDED_STATE_ON_GROUND) // PX4 allows disarm after this
				{
					static double last_trial_time = 0; // Avoid too frequent calls
					if (now_time.toSec() - last_trial_time > 1.0)
					{
						if (toggle_arm_disarm(false)) // disarm
						{
							print_once_flag = true;
							state = HOVER;
							ROS_INFO("\033[32m[px4ctrl] LAND --> HOVER \033[32m");
						}

						last_trial_time = now_time.toSec();
					}
				}
			}

			break;
		}

		case CMD_CTRL:
		{
			if (!cmd2_is_received(now_time))
			{
				state = HOVER;
				set_hov_with_odom();
				des = get_hover_des();
				ROS_INFO("\033[32m[px4ctrl] CMD_CTRL --> HOVER \033[32m");
			}
			else
			{
				des.p = odom_data.p;  
				des.v = al_desired_velocity_; // Use AL's output as desired velocity in CMD_CTRL mode
				des.a = Eigen::Vector3d::Zero();
				des.j = Eigen::Vector3d::Zero();
				des.yaw = uav_utils::get_yaw_from_quaternion(odom_data.q); 
				des.yaw_rate = 0.0;
			}

		    if (takeoff_land_data.triggered && takeoff_land_data.takeoff_land_cmd == quadrotor_msgs::TakeoffLand::LAND)
			{
				ROS_ERROR("[px4ctrl] Reject AUTO_LAND, which must be triggered in AUTO_HOVER. \
						Stop sending control commands for longer than %fs to let px4ctrl return to AUTO_HOVER first.",
						param.msg_timeout.cmd);
			}
			break;
		}

		default:
			break;
		}

		// STEP2: estimate thrust model
		if (state == HOVER || state == POLY_TRAJ || state == PNG_GUIDANCE || state == CMD_CTRL)
		{
			bool updated = controller.estimateThrustModel(imu_data.a, param);

			if (updated)
			{
				std_msgs::Float64 thr2acc_msg;
				thr2acc_msg.data = controller.getThr2Acc();
				thrust_model_pub.publish(thr2acc_msg);
			}
		}

		// STEP3: solve and update new control commands
		if (rotor_low_speed_during_land) // used at the start of auto takeoff
		{
			motors_idling(imu_data, u);
		}
	
		else
		{
			debug_msg = controller.calculateControl(des, odom_data, imu_data, u);
			debug_msg.header.stamp = now_time;
			debug_pub.publish(debug_msg);
		}

		// STEP4: publish control commands to mavros
		if (param.use_bodyrate_ctrl)
		{
			publish_bodyrate_ctrl(u, now_time);
		}
		else
		{
			publish_attitude_ctrl(u, now_time);
		}

}

void PX4CtrlFSM::motors_idling(const Imu_Data_t &imu, Controller_Output_t &u)
{
	u.q = imu.q;
	u.bodyrates = Eigen::Vector3d::Zero();
	u.thrust = 0.04;
}


Desired_State_t PX4CtrlFSM::get_hover_des()
{
	Desired_State_t des;
	des.p = hover_pose.head<3>();
	des.v = Eigen::Vector3d::Zero();
	des.a = Eigen::Vector3d::Zero();
	des.j = Eigen::Vector3d::Zero();
	des.yaw = hover_pose(3);
	des.yaw_rate = 0.0;

	return des;
}

Desired_State_t PX4CtrlFSM::get_cmd_des()
{
	Desired_State_t des;
	des.p = cmd_data.p;
	des.v = cmd_data.v;
	des.a = cmd_data.a;
	des.j = cmd_data.j;
	des.yaw = cmd_data.yaw;
	des.yaw_rate = cmd_data.yaw_rate;

	return des;
}

Desired_State_t PX4CtrlFSM::get_rotor_speed_up_des(const ros::Time now)
{
	double delta_t = (now - takeoff_land.toggle_takeoff_land_time).toSec();
	double des_a_z = exp((delta_t - AutoTakeoffLand_t::MOTORS_SPEEDUP_TIME) * 6.0) * 7.0 - 7.0; // Parameters 6.0 and 7.0 are just heuristic values which result in a saticfactory curve.
	if (des_a_z > 0.1)
	{
		ROS_ERROR("des_a_z > 0.1!, des_a_z=%f", des_a_z);
		des_a_z = 0.0;
	}

	Desired_State_t des;
	des.p = takeoff_land.start_pose.head<3>();
	des.v = Eigen::Vector3d::Zero();
	des.a = Eigen::Vector3d(0, 0, des_a_z);
	des.j = Eigen::Vector3d::Zero();
	des.yaw = takeoff_land.start_pose(3);
	des.yaw_rate = 0.0;

	return des;
}

Desired_State_t PX4CtrlFSM::get_takeoff_land_des(const double speed)
{
	ros::Time now = ros::Time::now();
	double delta_t = (now - takeoff_land.toggle_takeoff_land_time).toSec() - (speed > 0 ? AutoTakeoffLand_t::MOTORS_SPEEDUP_TIME : 0); // speed > 0 means takeoff
	// takeoff_land.last_set_cmd_time = now;

	// takeoff_land.start_pose(2) += speed * delta_t;

	Desired_State_t des;
	des.p = takeoff_land.start_pose.head<3>() + Eigen::Vector3d(0, 0, speed * delta_t);
	des.v = Eigen::Vector3d(0, 0, speed);
	des.a = Eigen::Vector3d::Zero();
	des.j = Eigen::Vector3d::Zero();
	des.yaw = takeoff_land.start_pose(3);
	des.yaw_rate = 0.0;

	return des;
}

void PX4CtrlFSM::set_hov_with_odom()
{
	hover_pose.head<3>() = odom_data.p;
	hover_pose(3) = get_yaw_from_quaternion(odom_data.q);

	last_set_hover_pose_time = ros::Time::now();
}

void PX4CtrlFSM::set_hov_with_rc()
{
	ros::Time now = ros::Time::now();
	double delta_t = (now - last_set_hover_pose_time).toSec();
	last_set_hover_pose_time = now;

	hover_pose(0) += rc_data.ch[1] * param.max_manual_vel * delta_t * (param.rc_reverse.pitch ? 1 : -1);
	hover_pose(1) += rc_data.ch[0] * param.max_manual_vel * delta_t * (param.rc_reverse.roll ? 1 : -1);
	hover_pose(2) += rc_data.ch[2] * param.max_manual_vel * delta_t * (param.rc_reverse.throttle ? 1 : -1);
	hover_pose(3) += rc_data.ch[3] * param.max_manual_vel * delta_t * (param.rc_reverse.yaw ? 1 : -1);

	if (hover_pose(2) < -0.3)
		hover_pose(2) = -0.3;

	// if (param.print_dbg)
	// {
	// 	static unsigned int count = 0;
	// 	if (count++ % 100 == 0)
	// 	{
	// 		cout << "hover_pose=" << hover_pose.transpose() << endl;
	// 		cout << "ch[0~3]=" << rc_data.ch[0] << " " << rc_data.ch[1] << " " << rc_data.ch[2] << " " << rc_data.ch[3] << endl;
	// 	}
	// }
}

void PX4CtrlFSM::set_start_pose_for_takeoff_land(const Odom_Data_t &odom)
{
	takeoff_land.start_pose.head<3>() = odom_data.p;
	takeoff_land.start_pose(3) = get_yaw_from_quaternion(odom_data.q);

	takeoff_land.toggle_takeoff_land_time = ros::Time::now();
}

bool PX4CtrlFSM::rc_is_received(const ros::Time &now_time)
{
	return (now_time - rc_data.rcv_stamp).toSec() < param.msg_timeout.rc;
}

bool PX4CtrlFSM::cmd_is_received(const ros::Time &now_time)
{
	return (now_time - cmd_data.rcv_stamp).toSec() < param.msg_timeout.cmd;
}
//test
bool PX4CtrlFSM::cmd2_is_received(const ros::Time &now_time)
{
	return (now_time - last_vel_received_time_).toSec() < param.msg_timeout.cmd;
}

bool PX4CtrlFSM::odom_is_received(const ros::Time &now_time)
{
	return (now_time - odom_data.rcv_stamp).toSec() < param.msg_timeout.odom;
}

bool PX4CtrlFSM::imu_is_received(const ros::Time &now_time)
{
	return (now_time - imu_data.rcv_stamp).toSec() < param.msg_timeout.imu;
}

bool PX4CtrlFSM::bat_is_received(const ros::Time &now_time)
{
	return (now_time - bat_data.rcv_stamp).toSec() < param.msg_timeout.bat;
}

bool PX4CtrlFSM::recv_new_odom()
{
	if (odom_data.recv_new_msg)
	{
		odom_data.recv_new_msg = false;
		return true;
	}

	return false;
}

void PX4CtrlFSM::publish_bodyrate_ctrl(const Controller_Output_t &u, const ros::Time &stamp)
{
	mavros_msgs::AttitudeTarget msg;

	msg.header.stamp = stamp;
	msg.header.frame_id = std::string("FCU");

	msg.type_mask = mavros_msgs::AttitudeTarget::IGNORE_ATTITUDE;

	msg.body_rate.x = u.bodyrates.x();
	msg.body_rate.y = u.bodyrates.y();
	msg.body_rate.z = u.bodyrates.z();

	msg.thrust = u.thrust;

	ctrl_FCU_pub.publish(msg);
}

void PX4CtrlFSM::publish_attitude_ctrl(const Controller_Output_t &u, const ros::Time &stamp)
{
	mavros_msgs::AttitudeTarget msg;

	msg.header.stamp = stamp;
	msg.header.frame_id = std::string("FCU");

	msg.type_mask = mavros_msgs::AttitudeTarget::IGNORE_ROLL_RATE |
					mavros_msgs::AttitudeTarget::IGNORE_PITCH_RATE |
					mavros_msgs::AttitudeTarget::IGNORE_YAW_RATE;

	msg.orientation.x = u.q.x();
	msg.orientation.y = u.q.y();
	msg.orientation.z = u.q.z();
	msg.orientation.w = u.q.w();

	msg.thrust = u.thrust;

	ctrl_FCU_pub.publish(msg);
}

void PX4CtrlFSM::publish_trigger(const nav_msgs::Odometry &odom_msg)
{
	geometry_msgs::PoseStamped msg;
	msg.header.frame_id = "world";
	msg.pose = odom_msg.pose.pose;

	traj_start_trigger_pub.publish(msg);
}

bool PX4CtrlFSM::toggle_offboard_mode(bool on_off)
{
	mavros_msgs::SetMode offb_set_mode;

	if (on_off)
	{
		state_data.state_before_offboard = state_data.current_state;
		if (state_data.state_before_offboard.mode == "OFFBOARD") // Not allowed
			state_data.state_before_offboard.mode = "MANUAL";

		offb_set_mode.request.custom_mode = "OFFBOARD";
		if (!(set_FCU_mode_srv.call(offb_set_mode) && offb_set_mode.response.mode_sent))
		{
			ROS_ERROR("Enter OFFBOARD rejected by PX4!");
			return false;
		}
	}
	else
	{
		offb_set_mode.request.custom_mode = state_data.state_before_offboard.mode;
		if (!(set_FCU_mode_srv.call(offb_set_mode) && offb_set_mode.response.mode_sent))
		{
			ROS_ERROR("Exit OFFBOARD rejected by PX4!");
			return false;
		}
	}

	return true;

	// if (param.print_dbg)
	// 	printf("offb_set_mode mode_sent=%d(uint8_t)\n", offb_set_mode.response.mode_sent);
}

bool PX4CtrlFSM::toggle_arm_disarm(bool arm)
{
	mavros_msgs::CommandBool arm_cmd;
	arm_cmd.request.value = arm;
	if (!(arming_client_srv.call(arm_cmd) && arm_cmd.response.success))
	{
		if (arm)
			ROS_ERROR("ARM rejected by PX4!");
		else
			ROS_ERROR("DISARM rejected by PX4!");

		return false;
	}

	return true;
}

void PX4CtrlFSM::reboot_FCU()
{
	// https://mavlink.io/en/messages/common.html, MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN(#246)
	mavros_msgs::CommandLong reboot_srv;
	reboot_srv.request.broadcast = false;
	reboot_srv.request.command = 246; // MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN
	reboot_srv.request.param1 = 1;	  // Reboot autopilot
	reboot_srv.request.param2 = 0;	  // Do nothing for onboard computer
	reboot_srv.request.confirmation = true;

	reboot_FCU_srv.call(reboot_srv);

	ROS_INFO("Reboot FCU");

	// if (param.print_dbg)
	// 	printf("reboot result=%d(uint8_t), success=%d(uint8_t)\n", reboot_srv.response.result, reboot_srv.response.success);
}

// ---- PNG Guidance ----
void PX4CtrlFSM::update_al_angular_velocity(const geometry_msgs::Vector3::ConstPtr& msg)
{
	al_angular_velocity_(0) = msg->x;
	al_angular_velocity_(1) = msg->y;
	al_angular_velocity_(2) = msg->z;
	last_al_control_time_ = ros::Time::now();
	al_control_received_ = true;
}

void PX4CtrlFSM::update_al_thrust_value(const geometry_msgs::Vector3::ConstPtr& msg)
{
	al_thrust_value_ = msg->x;  // thrust value is in the x field
	last_al_control_time_ = ros::Time::now();
	al_control_received_ = true;
}

void PX4CtrlFSM::update_al_desired_acceleration(const geometry_msgs::Vector3::ConstPtr& msg)
{
	al_desired_acceleration_(0) = msg->x;
	al_desired_acceleration_(1) = msg->y;
	al_desired_acceleration_(2) = msg->z;
	last_acc_received_time = ros::Time::now();
	al_acceleration_received_ = true;
}

void PX4CtrlFSM::update_al_desired_velocity(const geometry_msgs::Vector3::ConstPtr& msg)
{
	al_desired_velocity_(0) = msg->x;
	al_desired_velocity_(1) = msg->y;
	al_desired_velocity_(2) = msg->z;
	last_vel_received_time_ = ros::Time::now();
	al_velocity_received_ = true;
}

void PX4CtrlFSM::check_png_guidance_state()
{
	ros::Time now = ros::Time::now();
	double time_since_last_msg = (now - last_desired_vel_dir_time_).toSec();

	// Enter PNG_GUIDANCE if receiving desired_vel_dir and in offboard mode
	if (time_since_last_msg < PNG_TIMEOUT &&
	    state_data.current_state.mode == mavros_msgs::State::MODE_PX4_OFFBOARD &&
	    state != PNG_GUIDANCE && state != TAKEOFF && state != LAND)
	{
		state = PNG_GUIDANCE;
		ROS_INFO("\033[32m[px4ctrl] --> PNG_GUIDANCE \033[32m");
	}
	// Exit PNG_GUIDANCE if timeout or not in offboard
	else if (state == PNG_GUIDANCE &&
	         (time_since_last_msg >= PNG_TIMEOUT ||
	          state_data.current_state.mode != mavros_msgs::State::MODE_PX4_OFFBOARD))
	{
		state = HOVER;
		ROS_INFO("\033[33m[px4ctrl] PNG_GUIDANCE --> HOVER (timeout or mode change)\033[33m");
	}

	state = PNG_GUIDANCE;
}

