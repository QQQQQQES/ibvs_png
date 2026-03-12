// Auto-generated. Do not edit!

// (in-package ibvs_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class ImageFeatures {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.feature_points = null;
      this.feature_velocities = null;
      this.image_jacobian = null;
      this.num_features = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('feature_points')) {
        this.feature_points = initObj.feature_points
      }
      else {
        this.feature_points = [];
      }
      if (initObj.hasOwnProperty('feature_velocities')) {
        this.feature_velocities = initObj.feature_velocities
      }
      else {
        this.feature_velocities = [];
      }
      if (initObj.hasOwnProperty('image_jacobian')) {
        this.image_jacobian = initObj.image_jacobian
      }
      else {
        this.image_jacobian = [];
      }
      if (initObj.hasOwnProperty('num_features')) {
        this.num_features = initObj.num_features
      }
      else {
        this.num_features = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ImageFeatures
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [feature_points]
    // Serialize the length for message field [feature_points]
    bufferOffset = _serializer.uint32(obj.feature_points.length, buffer, bufferOffset);
    obj.feature_points.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [feature_velocities]
    // Serialize the length for message field [feature_velocities]
    bufferOffset = _serializer.uint32(obj.feature_velocities.length, buffer, bufferOffset);
    obj.feature_velocities.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Vector3.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [image_jacobian]
    bufferOffset = _arraySerializer.float64(obj.image_jacobian, buffer, bufferOffset, null);
    // Serialize message field [num_features]
    bufferOffset = _serializer.int32(obj.num_features, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ImageFeatures
    let len;
    let data = new ImageFeatures(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [feature_points]
    // Deserialize array length for message field [feature_points]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.feature_points = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.feature_points[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [feature_velocities]
    // Deserialize array length for message field [feature_velocities]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.feature_velocities = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.feature_velocities[i] = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [image_jacobian]
    data.image_jacobian = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [num_features]
    data.num_features = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 24 * object.feature_points.length;
    length += 24 * object.feature_velocities.length;
    length += 8 * object.image_jacobian.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ibvs_msgs/ImageFeatures';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '91c151d3e6d430698eaca9cd7aafd529';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    
    # Image feature points
    geometry_msgs/Point[] feature_points
    
    # Feature velocities
    geometry_msgs/Vector3[] feature_velocities
    
    # Image Jacobian matrix (flattened)
    float64[] image_jacobian
    
    # Number of features
    int32 num_features
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ImageFeatures(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.feature_points !== undefined) {
      resolved.feature_points = new Array(msg.feature_points.length);
      for (let i = 0; i < resolved.feature_points.length; ++i) {
        resolved.feature_points[i] = geometry_msgs.msg.Point.Resolve(msg.feature_points[i]);
      }
    }
    else {
      resolved.feature_points = []
    }

    if (msg.feature_velocities !== undefined) {
      resolved.feature_velocities = new Array(msg.feature_velocities.length);
      for (let i = 0; i < resolved.feature_velocities.length; ++i) {
        resolved.feature_velocities[i] = geometry_msgs.msg.Vector3.Resolve(msg.feature_velocities[i]);
      }
    }
    else {
      resolved.feature_velocities = []
    }

    if (msg.image_jacobian !== undefined) {
      resolved.image_jacobian = msg.image_jacobian;
    }
    else {
      resolved.image_jacobian = []
    }

    if (msg.num_features !== undefined) {
      resolved.num_features = msg.num_features;
    }
    else {
      resolved.num_features = 0
    }

    return resolved;
    }
};

module.exports = ImageFeatures;
