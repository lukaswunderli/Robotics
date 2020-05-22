source devel/setup.bash
terminator -e "./launchTurtlebot.sh" &
sleep 5
terminator -e "./launchEKF.sh" &
terminator -e "./launchTrajectory.sh" &
terminator -e "./launchTeleop.sh" &
