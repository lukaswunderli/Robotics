#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ProcessImage {
   public:
	ProcessImage(){

	    // Define a client service capable of requesting services from command_robot
	    client_ = n_.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
	    n_.setParam("turningRate",3.0);
	    n_.setParam("drivingRate",0.1);
	}

	// This callback function continuously executes and reads the image data
	void process_image_callback(const sensor_msgs::Image img)
	{

	    int white_pixel = 255;

	    // TODO: Loop through each pixel in the image and check if there's a bright white one
	    // Then, identify if this pixel falls in the left, mid, or right side of the image
	    // Depending on the white ball position, call the drive_bot function and pass velocities to it
	    // Request a stop when there's no white ball seen by the camera
	    int height = img.height;
	    int step = img.step;
	    float x = 0.0;
	    float z = 0.0;
	    float offset_accumulated = 0;
	    int count_total = 0;
	    for (int i = 0; i < height ; i++) {
		for (int j = 0; j < step; j++) {
		    if (img.data[i * step + j] == white_pixel) {
		        offset_accumulated += j - step / 2.0;
		        count_total++;
		    }
		}
	    }
	    float whitePixelRatio = count_total/float(height*step);
	    ROS_INFO_STREAM("whitePixelRatio: " + std::to_string(whitePixelRatio));

	    if (count_total == 0 || whitePixelRatio > 0.5) {
		x = 0.0;
		z = 0.0;
	    }
	    else {
		float turningRate = 0.0;
		float drivingRate = 0.0;
		float maxDrivingRate = 0.5;
		n_.getParam("turningRate",turningRate);
		n_.getParam("drivingRate",drivingRate);
		x = std::min(maxDrivingRate,drivingRate/whitePixelRatio);
		z = -turningRate * offset_accumulated / count_total / (step /2.0);
	    }
	    
	    // Send request to service
	    drive_robot(x, z);
	}

    private:

	// This function calls the command_robot service to drive the robot in the specified direction
	void drive_robot(float lin_x, float ang_z)
	{
	    // TODO: Request a service and pass the velocities to it to drive the robot
	    ROS_INFO_STREAM("Driving the robot to the target.");
	    
	    // Request service with velocities
	    ball_chaser::DriveToTarget srv;
	    srv.request.linear_x = lin_x;
	    srv.request.angular_z = ang_z;
	    
	    // Call the DriveToTarget service and pass the requested velocities
	    if (!client_.call(srv)) {
		    ROS_ERROR("Failed to call service DriveToTarget.");
		}
	}

	ros::ServiceClient client_;
        ros::NodeHandle n_;
};

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ProcessImage PIObject;
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, &PIObject);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
