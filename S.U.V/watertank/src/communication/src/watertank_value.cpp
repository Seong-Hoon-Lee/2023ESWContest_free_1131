#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>

ros::Publisher Pub_joystick;
ros::Subscriber sub_joystick;

std::string unity2jetson="unity/ref_base_vel_command";
std::string jetson2arduino="joystick_val_topic";


void joyCallback(const std_msgs::Float32MultiArray::ConstPtr& joy_array)
{    
    std_msgs::Float32MultiArray joystick_val;

    for(size_t i=0;i<12;i++){
        joystick_val.data.push_back(joy_array->data[i]);
    }

    Pub_joystick.publish(joystick_val);
    joystick_val.data.clear();

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "joystick_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(10);
    
    Pub_joystick = nh.advertise<std_msgs::Float32MultiArray>(jetson2arduino, 1);
    sub_joystick = nh.subscribe<std_msgs::Float32MultiArray>(unity2jetson, 1, joyCallback);

    while(ros::ok())
    {
        // std_msgs::Float32MultiArray joystick_val;

        // joystick_val.data.push_back(1.0);
        // joystick_val.data.push_back(5.0);

        // Pub_joystick.publish(joystick_val);
        // joystick_val.data.clear();

        ros::spinOnce();
        loop_rate.sleep();
    }
}







