#!/bin/bash

xterm -e " source devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/turtlebot_simulator/turtlebot_gazebo/worlds/playground.world"; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 7
xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/turtlebot_simulator/turtlebot_gazebo/maps/playground.yaml"; roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 5
xterm  -e "source devel/setup.bash; roslaunch rviz rviz -d src/rvizConfig/navigation.rviz" &
sleep 5
xterm  -e "source devel/setup.bash; rosrun add_markers add_markers"
sleep 5
xterm  -e "source devel/setup.bash; rosrun pick_objects pick_objects"

