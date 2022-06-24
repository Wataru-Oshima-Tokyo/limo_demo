#include "unistd.h"
#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/Bool.h"
#include "sound_play/sound_play.h"
#include "limo_base/LimoStatus.h"

float threshold;
class BATTERY_CHECK{
	public:
		sound_play::SoundClient sound_client;

		ros::Subscriber sub = n.subscribe("limo_status", 10, batteryCallback);
		ros::Publisher charge_pub = n.advertise<std_msgs::Bool>("charge",1000);
		
		BATTERY_CHECK();
		~BATTERY_CHECK();


	BATTERY_CHECK(){
		ros::NodeHandle n;
		ros::NodeHandle pnh("~");
		pnh.getParam("threshold", threshold);
	}
	~BATTERY_CHECK(){}

	void batteryCallback(const limo_base::LimoStatus& msg)
	{
		std_msgs::Bool charge;
		sound_play::SoundClient sound_client;
		float voltage = msg.battery_voltage;
		ROS_INFO("battery_voltage: %f", voltage);
		if (voltage < threshold)
		{
			sound_client.playWave("/home/agilex/agilex_ws/src/limo_ros/limo_demo/voice/juuden.wav", 1.0);
			sleep(3);
			charge = true;
		}else{
			charge = false;
		}
		charge_pub.publish(charge);
	}
};


int main(int argc, char **argv)
{
	ros::init(argc, argv, "battery");
	BATTERY_CHECK btc;
	ros::spin();

	return 0;
}
