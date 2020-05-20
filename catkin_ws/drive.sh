source devel/setup.bash


#rostopic pub /cmd_vel geometry_msgs/Twist '{linear: {x: 0.1, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.1}}'

case "$1" in
	straight)
		rosservice call /ball_chaser/command_robot "{linear_x: 0.5, angular_z: 0.0}"
		;;
	left)
		rosservice call /ball_chaser/command_robot "{linear_x: 0.0, angular_z: 0.5}"
		;;
	right)
		rosservice call /ball_chaser/command_robot "{linear_x: 0.5, angular_z: -0.5}"
		;;
	stop)
		rosservice call /ball_chaser/command_robot "{linear_x: 0.0, angular_z: 0.0}"
		;;
	*)
		echo "unnknown command"
		;;
esac
