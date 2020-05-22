source devel/setup.bash
terminator -e "./launchMyRobot.sh" &
sleep 5
terminator -e "./launchBallChaser.sh" &
