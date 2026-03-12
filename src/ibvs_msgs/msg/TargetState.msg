Header header

# Target position in image coordinates
float64 u
float64 v

# Target velocity in image plane
float64 u_dot
float64 v_dot

# Target depth (distance from camera)
float64 depth

# Target 3D position in camera frame
geometry_msgs/Point position

# Target 3D velocity in camera frame
geometry_msgs/Vector3 velocity

# Confidence score
float64 confidence
