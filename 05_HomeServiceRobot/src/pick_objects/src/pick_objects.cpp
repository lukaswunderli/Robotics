#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/tf.h>


// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle nh;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  double minRotVel = 0.1;
  double maxRotVel = 0.5;
  double minTransVel = 0.5;
  double maxTransVel = 1.0;
  nh.setParam("move_base/DWAPlannerROS/min_rot_vel",minRotVel);
  nh.setParam("move_base/DWAPlannerROS/max_rot_vel",maxRotVel);
  nh.setParam("move_base/DWAPlannerROS/min_trans_vel",minTransVel);
  nh.setParam("move_base/DWAPlannerROS/max_trans_vel",maxTransVel);

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach

  float goals[2][3] = { {3, 1, -1.57}, {3.2, 0.584, -1.57}  };

  int num_points = 2;

  for (int i=0; i < num_points; i++){

      goal.target_pose.pose.position.x = goals[i][0];
      goal.target_pose.pose.position.y = goals[i][1];
      goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(goals[i][2]);

       // Send the goal position and orientation for the robot to reach
      ROS_INFO("Sending goal");
      ac.sendGoal(goal);

      // Wait an infinite time for the results
      ac.waitForResult();

      // Check if the robot reached its goal
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Goal reached!");
      else
        ROS_INFO("Failed to reach goal for some reason");
      ros::Duration(5.0).sleep();
  }

  return 0;
}
