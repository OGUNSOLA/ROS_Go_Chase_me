#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"


// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities


bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
    ball_chaser::DriveToTarget::Response& res)
{
// Initialize the ROS system and become a node.
  
  ros::NodeHandle nh;

  // Create a publisher object.
   motor_command_publisher = nh.advertise<geometry_msgs::Twist>(
    "/cmd_vel", 1000);
    geometry_msgs::Twist command;
    command.linear.x = req.linear_x;
    command.angular.z = req.angular_z;
 // Publish angles to drive the robot
        motor_command_publisher.publish(command);

res.msg_feedback = "Pose: " + std::to_string(req.linear_x) + " " + std::to_string(req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle nh;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function

    ros::ServiceServer service = nh.advertiseService("/ball_chaser/command_robot", handle_drive_request);

  
    

    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}
