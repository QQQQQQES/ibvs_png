// /*****************************************************************************************
//  * 航点发布器
//  * 功能：从XML文件加载航点，并根据/position_cmd话题的接收间隔自动发布下一个航点。
//  ******************************************************************************************/
// #include <ros/ros.h>
// #include <geometry_msgs/PoseStamped.h>
// #include <quadrotor_msgs/PositionCommand.h>
// #include <quadrotor_msgs/TakeoffLand.h> //降落消息类型
// #include <vector>
// #include <fstream>
// #include <cmath>
// #include <tinyxml.h>  // XML文件解析

// #define PI 3.14159265358979

// class WaypointPublisher
// {
// private:
//     ros::NodeHandle nh;
    
//     // 订阅和发布
//     ros::Subscriber twist_sub;
//     ros::Publisher waypoint_pub;
//     ros::Timer publish_timer; 
    
//     // 降落指令发布器
//     ros::Publisher takeoff_land_pub; 

//     // 航点管理
//     std::vector<geometry_msgs::PoseStamped> waypoints;
//     size_t current_waypoint_index;
//     std::string waypoints_file_;

//     // 状态和时间
//     ros::Time last_cmd_time;
//     const double cmd_timeout_sec = 1.5; 
    
//     // 标志位：用于处理启动时 ROS Time 的巨大跳跃问题
//     bool first_check_passed; 
    
//     // 标志位，表示所有航点是否已发布完毕
//     bool all_waypoints_published; 
    
// public:
//     WaypointPublisher();
//     bool load_waypoints_from_xml(const std::string& filename);
//     void load_waypoints();
//     void publish_next_waypoint();
//     void twist_cb(const quadrotor_msgs::PositionCommand::ConstPtr& msg);
//     void check_and_publish_waypoint(const ros::TimerEvent&);
// };

// WaypointPublisher::WaypointPublisher()
//     // 初始化标志位
//     : current_waypoint_index(0), first_check_passed(false), all_waypoints_published(false) 
// {
//     // 初始化最后命令时间为当前时间
//     last_cmd_time = ros::Time::now();

//     // 话题订阅和发布
//     twist_sub = nh.subscribe("/position_cmd", 1, &WaypointPublisher::twist_cb, this);
//     waypoint_pub = nh.advertise<geometry_msgs::PoseStamped>("/goal", 1, true); 
//     // 初始化降落指令 Publisher
//     takeoff_land_pub = nh.advertise<quadrotor_msgs::TakeoffLand>("/px4ctrl/takeoff_land", 1); 

//     // 获取航点文件路径参数
//     ros::NodeHandle private_nh("~");
//     char const* home = getenv("HOME");
//     std::string default_file = std::string(home) + "/waypoints_in_world.xml";
//     private_nh.param("waypoints_file", waypoints_file_, default_file);
    
//     // 1. 加载航点
//     load_waypoints();

//     // 2. 设置定时器：每 0.1 秒检查一次是否需要发布下一个航点
//     publish_timer = nh.createTimer(ros::Duration(0.1), &WaypointPublisher::check_and_publish_waypoint, this);
    
//     // 3. 启动后立即发布第一个航点
//     if (!waypoints.empty()) {
//         publish_next_waypoint();
//         // 在发布第一个航点后，立即将计时器重置为当前时间。
//         last_cmd_time = ros::Time::now(); 
//     }
// }

// /**
//  * @brief 接收 /position_cmd 话题的回调函数，用于重置超时计时器。
//  */
// void WaypointPublisher::twist_cb(const quadrotor_msgs::PositionCommand::ConstPtr& msg)
// {
//     // 收到数据，更新时间
//     last_cmd_time = ros::Time::now();
//     // 只要收到了第一个命令，就认为时间同步正常了
//     first_check_passed = true; 
// }

// /**
//  * @brief 检查 /position_cmd 是否超时，并发布下一个航点或降落指令。
//  */
// void WaypointPublisher::check_and_publish_waypoint(const ros::TimerEvent&)
// {
//     // 检查 /position_cmd 是否超时
//     double time_since_last_cmd = (ros::Time::now() - last_cmd_time).toSec();
    
//     // 降落逻辑：如果所有航点已发布
//     if (all_waypoints_published)
//     {
//         if (time_since_last_cmd > cmd_timeout_sec)
//         {
//             // 超时，发布降落指令 (takeoff_land_cmd: 2 代表 Land)
//             quadrotor_msgs::TakeoffLand land_cmd;
//             land_cmd.takeoff_land_cmd = 2; 
//             takeoff_land_pub.publish(land_cmd);
            
//             ROS_INFO("Land command published! Timeout %.2f s > %.1f s. Mission complete.", time_since_last_cmd, cmd_timeout_sec);
            
//             // 停止定时器，任务完成
//             publish_timer.stop();
//         }
//         return;
//     }
    
//     // ----------------------------------------------------
//     // 航点发布逻辑：处理 ROS Time 跳跃问题
//     // ----------------------------------------------------
    
//     // 核心修正逻辑：处理启动时 ROS Time 的巨大跳跃
//     if (!first_check_passed && time_since_last_cmd > 10.0 * cmd_timeout_sec)
//     {
//         ROS_WARN("Detected initial ROS Time jump (%.2f s). Resetting internal timer and skipping this check cycle.", 
//                  time_since_last_cmd);
//         last_cmd_time = ros::Time::now();
//         first_check_passed = true; // 标记，避免下次重复此特殊处理
//         return;
//     }
    
//     first_check_passed = true; // 确保在时间差不大的情况下，也标记为已完成初始化检查
    
//     if (time_since_last_cmd > cmd_timeout_sec)
//     {
//         // 超时，发布下一个航点
//         ROS_WARN("Position command timeout (%.2f s > %.1f s). Publishing next waypoint.", 
//                  time_since_last_cmd, cmd_timeout_sec);
//         publish_next_waypoint();
        
//         // 立即重置计时，防止在同一周期内重复发布
//         last_cmd_time = ros::Time::now(); 
//     }
// }

// /**
//  * @brief 发布当前索引的航点并递增索引。
//  */
// void WaypointPublisher::publish_next_waypoint()
// {
//     if (current_waypoint_index < waypoints.size())
//     {
//         waypoints[current_waypoint_index].header.stamp = ros::Time::now();
//         waypoint_pub.publish(waypoints[current_waypoint_index]);
        
//         double qx = waypoints[current_waypoint_index].pose.orientation.x;
//         double qy = waypoints[current_waypoint_index].pose.orientation.y;
//         double qz = waypoints[current_waypoint_index].pose.orientation.z;
//         double qw = waypoints[current_waypoint_index].pose.orientation.w;
        
//         double yaw_rad = atan2(2*(qw*qz + qx*qy), 1 - 2*(qy*qy + qz*qz));
//         double yaw_deg = yaw_rad * 180.0 / PI;
        
//         ROS_INFO("✅ Publishing waypoint %zu/%zu: (%.2f, %.2f, %.2f) Yaw(%.2f deg)", 
//                  current_waypoint_index + 1, 
//                  waypoints.size(),
//                  waypoints[current_waypoint_index].pose.position.x,
//                  waypoints[current_waypoint_index].pose.position.y,
//                  waypoints[current_waypoint_index].pose.position.z,
//                  yaw_deg); 
        
//         current_waypoint_index++;
//     }
//     else
//     {
//         // 所有航点发布完毕，设置标志位
//         ROS_INFO("Last waypoint published. Waiting for final command timeout to trigger land.");
//         all_waypoints_published = true;
//     }
// }

// /**
//  * @brief 从XML文件加载航点。
//  */
// bool WaypointPublisher::load_waypoints_from_xml(const std::string& filename)
// {
//     // 检查文件是否存在
//     std::ifstream file(filename);
//     if (!file.good())
//     {
//         ROS_WARN("Waypoints file not found: %s", filename.c_str());
//         return false;
//     }
//     file.close();
    
//     try
//     {
//         TiXmlDocument doc(filename.c_str());
//         if (!doc.LoadFile())
//         {
//             ROS_ERROR("Failed to load XML file: %s", filename.c_str());
//             return false;
//         }
        
//         TiXmlElement* root = doc.RootElement();
//         if (!root || std::string(root->Value()) != "waypoint_list")
//         {
//             ROS_ERROR("Invalid waypoints file format: Root must be <waypoint_list>");
//             return false;
//         }
        
//         waypoints.clear();
        
//         std::string frame_id = "world";
//         TiXmlElement* frame_element = root->FirstChildElement("frame");
//         if (frame_element && frame_element->Attribute("id"))
//         {
//             frame_id = frame_element->Attribute("id");
//         }
        
//         int count = 0;
//         for (TiXmlElement* waypoint = root->FirstChildElement("waypoint");
//              waypoint != nullptr;
//              waypoint = waypoint->NextSiblingElement("waypoint"))
//         {
//             geometry_msgs::PoseStamped wp;
//             wp.header.frame_id = frame_id;
            
//             // 读取位置
//             TiXmlElement* position = waypoint->FirstChildElement("position");
//             if (position)
//             {
//                 position->QueryDoubleAttribute("x", &wp.pose.position.x);
//                 position->QueryDoubleAttribute("y", &wp.pose.position.y);
//                 position->QueryDoubleAttribute("z", &wp.pose.position.z);
//             }
            
//             // 读取方向（四元数），如果未定义则默认为 (0, 0, 0, 1)
//             TiXmlElement* orientation = waypoint->FirstChildElement("orientation");
//             wp.pose.orientation.w = 1.0;
//             if (orientation)
//             {
//                 orientation->QueryDoubleAttribute("x", &wp.pose.orientation.x);
//                 orientation->QueryDoubleAttribute("y", &wp.pose.orientation.y);
//                 orientation->QueryDoubleAttribute("z", &wp.pose.orientation.z);
//                 orientation->QueryDoubleAttribute("w", &wp.pose.orientation.w);
//             }
            
//             // 归一化四元数（保留原逻辑，确保安全）
//             double norm = sqrt(wp.pose.orientation.x * wp.pose.orientation.x +
//                              wp.pose.orientation.y * wp.pose.orientation.y +
//                              wp.pose.orientation.z * wp.pose.orientation.z +
//                              wp.pose.orientation.w * wp.pose.orientation.w);
//             if (norm > 0.0001)
//             {
//                 wp.pose.orientation.x /= norm;
//                 wp.pose.orientation.y /= norm;
//                 wp.pose.orientation.z /= norm;
//                 wp.pose.orientation.w /= norm;
//             }
            
//             waypoints.push_back(wp);
//             count++;
            
//             // 打印航点信息 (仅在加载时打印位置，发布时打印Yaw)
//             ROS_INFO("Loaded waypoint %d: pos(%.2f, %.2f, %.2f)", 
//                      count, 
//                      wp.pose.position.x, wp.pose.position.y, wp.pose.position.z);
//         }
        
//         ROS_INFO("Successfully loaded %d waypoints from: %s", count, filename.c_str());
//         return true;
//     }
//     catch (const std::exception& e)
//     {
//         ROS_ERROR("Exception while loading waypoints: %s", e.what());
//         return false;
//     }
// }

// /**
//  * @brief 航点加载入口函数。
//  */
// void WaypointPublisher::load_waypoints()
// {
//     ROS_INFO("Loading waypoints from file: %s", waypoints_file_.c_str());
    
//     // 尝试从XML文件加载
//     if (load_waypoints_from_xml(waypoints_file_))
//     {
//         ROS_INFO("Waypoints loaded from XML file successfully!");
//     } else {
//         ROS_ERROR("Failed to load any waypoints. Waypoint Publisher will be idle.");
//     }
// }


// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "waypoint_publisher");
//     setlocale(LC_ALL,"");
//     ROS_INFO("--------------- Start Waypoint Publisher ---------------");
//     WaypointPublisher publisher;
//     ros::spin();
//     return 0;
// }



/*****************************************************************************************
 * 航点发布器
 * 功能：从XML文件加载航点，并根据/position_cmd话题的接收间隔自动发布下一个航点。
 ******************************************************************************************/
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <quadrotor_msgs/PositionCommand.h>
#include <quadrotor_msgs/TakeoffLand.h> //降落消息类型
#include <nav_msgs/Odometry.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <tinyxml.h>  // XML文件解析

#define PI 3.14159265358979

class WaypointPublisher
{
private:
    ros::NodeHandle nh;
    
    // 订阅和发布
    ros::Subscriber twist_sub;
    ros::Publisher waypoint_pub;
    ros::Subscriber odom_sub; 
    ros::Timer publish_timer; 
    
    // 降落指令发布器
    ros::Publisher takeoff_land_pub; 
    
    // 航点管理
    std::vector<geometry_msgs::PoseStamped> waypoints;
    size_t current_waypoint_index;
    std::string waypoints_file_;

    // 状态和时间
    ros::Time last_cmd_time;
    const double cmd_timeout_sec = 1.5; 
    
    // 标志位：用于处理启动时 ROS Time 的巨大跳跃问题
    bool first_check_passed; 
    
    // 标志位，表示所有航点是否已发布完毕
    bool all_waypoints_published; 

    //存储当前无人机位置
    geometry_msgs::Point current_position; 
    //目标点误差阈值
    const double pos_tolerance = 0.15; // 0.15米阈值
    
public:
    WaypointPublisher();
    bool load_waypoints_from_xml(const std::string& filename);
    void load_waypoints();
    void publish_next_waypoint();
    void twist_cb(const quadrotor_msgs::PositionCommand::ConstPtr& msg);
    void odom_cb(const nav_msgs::Odometry::ConstPtr& msg); 
    void check_and_publish_waypoint(const ros::TimerEvent&);
};

WaypointPublisher::WaypointPublisher()
    // 初始化标志位
    : current_waypoint_index(0), first_check_passed(false), all_waypoints_published(false) 
{
    // 初始化最后命令时间为当前时间
    last_cmd_time = ros::Time::now();
    // 确保 current_position 初始为零
    current_position.x = current_position.y = current_position.z = 0.0;

    // 话题订阅和发布
    twist_sub = nh.subscribe("/position_cmd", 1, &WaypointPublisher::twist_cb, this);
    odom_sub = nh.subscribe("/LIVO2/imu_propagate", 1, &WaypointPublisher::odom_cb, this); 
    waypoint_pub = nh.advertise<geometry_msgs::PoseStamped>("/goal", 1, true); 
    takeoff_land_pub = nh.advertise<quadrotor_msgs::TakeoffLand>("/px4ctrl/takeoff_land", 1); 

    // 获取航点文件路径参数
    ros::NodeHandle private_nh("~");
    char const* home = getenv("HOME");
    std::string default_file = std::string(home) + "/waypoints_in_world.xml";
    private_nh.param("waypoints_file", waypoints_file_, default_file);
    
    // 1. 加载航点
    load_waypoints();

    // 2. 设置定时器：每 0.1 秒检查一次是否需要发布下一个航点
    publish_timer = nh.createTimer(ros::Duration(0.1), &WaypointPublisher::check_and_publish_waypoint, this);
    
    // 3. 启动后立即发布第一个航点
    if (!waypoints.empty()) {
        publish_next_waypoint();
        // 在发布第一个航点后，立即将计时器重置为当前时间。
        last_cmd_time = ros::Time::now(); 
    }
}

/**
 * @brief 接收 /position_cmd 话题的回调函数，用于重置超时计时器。
 */
void WaypointPublisher::twist_cb(const quadrotor_msgs::PositionCommand::ConstPtr& msg)
{
    // 收到数据，更新时间
    last_cmd_time = ros::Time::now();
    // 只要收到了第一个命令，就认为时间同步正常了
    first_check_passed = true; 
}

/**
 * @brief 接收当前位置信息的回调函数。
 */
void WaypointPublisher::odom_cb(const nav_msgs::Odometry::ConstPtr& msg)
{
    current_position = msg->pose.pose.position;
}


/**
 * @brief 检查 /position_cmd 是否超时，并发布下一个航点或降落指令。
 */
void WaypointPublisher::check_and_publish_waypoint(const ros::TimerEvent&)
{
    // 检查 /position_cmd 是否超时
    double time_since_last_cmd = (ros::Time::now() - last_cmd_time).toSec();
    
    // ----------------------------------------------------
    // 降落逻辑：如果所有航点已发布
    // ----------------------------------------------------
    if (all_waypoints_published)
    {
        // 只有在已经成功发布过至少一个航点时，才进行降落检查
        if (current_waypoint_index > 0)
        {
            size_t final_index = current_waypoint_index - 1;
            
            // 检查是否已到达最后一个航点的位置
            bool arrived_at_final_waypoint = 
                std::abs(current_position.x - waypoints[final_index].pose.position.x) < pos_tolerance &&
                std::abs(current_position.y - waypoints[final_index].pose.position.y) < pos_tolerance &&
                std::abs(current_position.z - waypoints[final_index].pose.position.z) < pos_tolerance;

            if (!arrived_at_final_waypoint)
            {
                // 尚未到达最后一个航点，继续等待
                ROS_INFO_THROTTLE(1.0, "Mission complete, but waiting to reach final position (%.2f, %.2f, %.2f) before landing. Current: (%.2f, %.2f, %.2f)",
                                 waypoints[final_index].pose.position.x,
                                 waypoints[final_index].pose.position.y,
                                 waypoints[final_index].pose.position.z,
                                 current_position.x, current_position.y, current_position.z);
                return;
            }
            
            // 达到最后一个航点位置后，等待超时（1.5秒）来触发降落
            if (time_since_last_cmd > cmd_timeout_sec)
            {
                // 超时，发布降落指令 (takeoff_land_cmd: 2 代表 Land)
                quadrotor_msgs::TakeoffLand land_cmd;
                land_cmd.takeoff_land_cmd = 2; 
                takeoff_land_pub.publish(land_cmd);
                
                ROS_INFO("🚁 Land command published! Timeout %.2f s > %.1f s. Mission complete.", time_since_last_cmd, cmd_timeout_sec);
                
                // 停止定时器，任务完成
                publish_timer.stop();
            }
        }
        return;
    }
    
    // ----------------------------------------------------
    // 航点发布逻辑
    // ----------------------------------------------------
    
    //处理启动时 ROS Time 的巨大跳跃
    if (!first_check_passed && time_since_last_cmd > 10.0 * cmd_timeout_sec)
    {
        ROS_WARN("Detected initial ROS Time jump (%.2f s). Resetting internal timer and skipping this check cycle.", 
                 time_since_last_cmd);
        last_cmd_time = ros::Time::now();
        first_check_passed = true; 
        return;
    }
    
    first_check_passed = true; 
    
    // 约束条件 1：如果不是第一个航点，必须先判断是否到达上一个目标点
    if (current_waypoint_index > 0 && current_waypoint_index <= waypoints.size())
    {
        size_t prev_index = current_waypoint_index - 1;
        
        // 计算与上一个目标点的距离误差
        double dx = std::abs(current_position.x - waypoints[prev_index].pose.position.x);
        double dy = std::abs(current_position.y - waypoints[prev_index].pose.position.y);
        double dz = std::abs(current_position.z - waypoints[prev_index].pose.position.z);

        if (dx > pos_tolerance || dy > pos_tolerance || dz > pos_tolerance)
        {
            // 位置没到，直接返回，不允许发布下一个航点
            return;
        }
        // 位置已到达，允许继续进行超时检查
    }
    
    // 约束条件 2：超时检查 (只有位置已到达，或当前是第一个航点时才会执行到这里)
    if (time_since_last_cmd > cmd_timeout_sec)
    {
        // 超时，发布下一个航点
        ROS_WARN("Position command timeout (%.2f s > %.1f s). Publishing next waypoint.", 
                 time_since_last_cmd, cmd_timeout_sec);
        publish_next_waypoint();
        
        // 立即重置计时，防止在同一周期内重复发布
        last_cmd_time = ros::Time::now(); 
    }
}

/**
 * @brief 发布当前索引的航点并递增索引。
 */
void WaypointPublisher::publish_next_waypoint()
{
    if (current_waypoint_index < waypoints.size())
    {
        waypoints[current_waypoint_index].header.stamp = ros::Time::now();
        waypoint_pub.publish(waypoints[current_waypoint_index]);
        
        double qx = waypoints[current_waypoint_index].pose.orientation.x;
        double qy = waypoints[current_waypoint_index].pose.orientation.y;
        double qz = waypoints[current_waypoint_index].pose.orientation.z;
        double qw = waypoints[current_waypoint_index].pose.orientation.w;
        
        double yaw_rad = atan2(2*(qw*qz + qx*qy), 1 - 2*(qy*qy + qz*qz));
        double yaw_deg = yaw_rad * 180.0 / PI;
        
        ROS_INFO("✅ Publishing waypoint %zu/%zu: (%.2f, %.2f, %.2f) Yaw(%.2f deg)", 
                 current_waypoint_index + 1, 
                 waypoints.size(),
                 waypoints[current_waypoint_index].pose.position.x,
                 waypoints[current_waypoint_index].pose.position.y,
                 waypoints[current_waypoint_index].pose.position.z,
                 yaw_deg); 
        
        current_waypoint_index++;
    }
    else
    {
        // 所有航点发布完毕，设置标志位
        ROS_INFO("Last waypoint published. Waiting for position arrival and final command timeout to trigger land.");
        all_waypoints_published = true;
    }
}

/**
 * @brief 从XML文件加载航点。
 */
bool WaypointPublisher::load_waypoints_from_xml(const std::string& filename)
{
    // 检查文件是否存在
    std::ifstream file(filename);
    if (!file.good())
    {
        ROS_WARN("Waypoints file not found: %s", filename.c_str());
        return false;
    }
    file.close();
    
    try
    {
        TiXmlDocument doc(filename.c_str());
        if (!doc.LoadFile())
        {
            ROS_ERROR("Failed to load XML file: %s", filename.c_str());
            return false;
        }
        
        TiXmlElement* root = doc.RootElement();
        if (!root || std::string(root->Value()) != "waypoint_list")
        {
            ROS_ERROR("Invalid waypoints file format: Root must be <waypoint_list>");
            return false;
        }
        
        waypoints.clear();
        
        std::string frame_id = "world";
        TiXmlElement* frame_element = root->FirstChildElement("frame");
        if (frame_element && frame_element->Attribute("id"))
        {
            frame_id = frame_element->Attribute("id");
        }
        
        int count = 0;
        for (TiXmlElement* waypoint = root->FirstChildElement("waypoint");
             waypoint != nullptr;
             waypoint = waypoint->NextSiblingElement("waypoint"))
        {
            geometry_msgs::PoseStamped wp;
            wp.header.frame_id = frame_id;
            
            // 读取位置
            TiXmlElement* position = waypoint->FirstChildElement("position");
            if (position)
            {
                position->QueryDoubleAttribute("x", &wp.pose.position.x);
                position->QueryDoubleAttribute("y", &wp.pose.position.y);
                position->QueryDoubleAttribute("z", &wp.pose.position.z);
            }
            
            // 读取方向（四元数），如果未定义则默认为 (0, 0, 0, 1)
            TiXmlElement* orientation = waypoint->FirstChildElement("orientation");
            wp.pose.orientation.w = 1.0;
            if (orientation)
            {
                orientation->QueryDoubleAttribute("x", &wp.pose.orientation.x);
                orientation->QueryDoubleAttribute("y", &wp.pose.orientation.y);
                orientation->QueryDoubleAttribute("z", &wp.pose.orientation.z);
                orientation->QueryDoubleAttribute("w", &wp.pose.orientation.w);
            }
            
            // 归一化四元数（保留原逻辑，确保安全）
            double norm = sqrt(wp.pose.orientation.x * wp.pose.orientation.x +
                             wp.pose.orientation.y * wp.pose.orientation.y +
                             wp.pose.orientation.z * wp.pose.orientation.z +
                             wp.pose.orientation.w * wp.pose.orientation.w);
            if (norm > 0.0001)
            {
                wp.pose.orientation.x /= norm;
                wp.pose.orientation.y /= norm;
                wp.pose.orientation.z /= norm;
                wp.pose.orientation.w /= norm;
            }
            
            waypoints.push_back(wp);
            count++;
            
            // 打印航点信息 (仅在加载时打印位置，发布时打印Yaw)
            ROS_INFO("Loaded waypoint %d: pos(%.2f, %.2f, %.2f)", 
                     count, 
                     wp.pose.position.x, wp.pose.position.y, wp.pose.position.z);
        }
        
        ROS_INFO("Successfully loaded %d waypoints from: %s", count, filename.c_str());
        return true;
    }
    catch (const std::exception& e)
    {
        ROS_ERROR("Exception while loading waypoints: %s", e.what());
        return false;
    }
}

/**
 * @brief 航点加载入口函数。
 */
void WaypointPublisher::load_waypoints()
{
    ROS_INFO("Loading waypoints from file: %s", waypoints_file_.c_str());
    
    // 尝试从XML文件加载
    if (load_waypoints_from_xml(waypoints_file_))
    {
        ROS_INFO("Waypoints loaded from XML file successfully!");
    } else {
        ROS_ERROR("Failed to load any waypoints. Waypoint Publisher will be idle.");
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "waypoint_publisher");
    setlocale(LC_ALL,"");
    ROS_INFO("--------------- Start Waypoint Publisher ---------------");
    WaypointPublisher publisher;
    ros::spin();
    return 0;
}