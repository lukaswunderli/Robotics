#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//TODO: Include the ball_chaser "DriveToTarget" header file

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function

    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
    while (ros::ok()) {
        // Create a motor_command object of type geometry_msgs::Twist
        geometry_msgs::Twist motor_command;
        // Set wheel velocities, forward [0.5, 0.0]
        motor_command.linear.x = 0.5;
        motor_command.angular.z = 0.0;
        // Publish angles to drive the robot
        motor_command_publisher.publish(motor_command);
    }

    // TODO: Handle ROS communication events
    //ros::spin();

    return 0;
}

Take a look at this program and try to understand what is happening. Then, copy it to drive_bot.cpp, and make the necessary changes to define a ball_chaser/command_robot service.
Edit CMakeLists.txt

After you write the server node in C++, you’ll have to add the following dependencies:

    Add the add_compile_options for C++ 11 dependency, this step is optional and depends on your code
    Add the add_service_files dependency which defines the DriveToTarget.srv file
    Add the generate_messages dependency
    Add include_directories dependency
    Add the add_executable, target_link_libraries, and add_dependencies dependency for your drive_bot.cppscript

Build Package

Now that you’ve included specific instructions for your drive_bot.cpp code in CMakeLists.txt file, compile it with:

$ cd /home/workspace/catkin_ws/
$ catkin_make

Test drive_bot.cpp

To test if the service you wrote is working, first launch the robot inside your world. Then call the /ball_chaser/command_robot service to drive the robot forward, left, and then right.

1- Launch the robot inside your world

$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ roslaunch my_robot world.launch

2- Run the drive_bot node

$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash
$ rosrun ball_chaser drive_bot

3- Request a ball_chaser/command_robot service

Test the service by requesting different sets of velocities from the terminal.

Open a new terminal while all the nodes are running and type:

$ cd /home/workspace/catkin_ws/
$ source devel/setup.bash

$ rosservice call /ball_chaser/command_robot "linear_x: 0.5
angular_z: 0.0"  # This request should drive your robot forward

$ rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: 0.5"  # This request should drive your robot left

$ rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: -0.5"  # This request should drive your robot right

$ rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: 0.0"  # This request should bring your robot to a complete stop


