# RoboND-Home-Service-Robot

The final project of the Udacity Robotics Nanodegree incorporates a number of elements from previous projects, rolling them into a single solution that would actually be required to engineer a home service robot:
1. Build a simulated map using Gazebo building editor
2. Build a map of the environment using gmapping and teleop.
3. Use Adaptive Monte Carlo Localisation to detect the robot position within the known map.
4. Use the ROS move_base library to plot a path to a target pose and navigate to it.
5. Write a custom node to encompass the path planning and driving libraries, listening for goal poses.
6. Write a custom node to publish goal poses for the robot, then compare these to the actual pose (odometry topic) to determine success.
