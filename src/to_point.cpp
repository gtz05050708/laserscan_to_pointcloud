#include <ros/ros.h>

#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Point32.h"
#include "sensor_msgs/ChannelFloat32.h"


ros::Publisher scan3d_pub;



void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    sensor_msgs::LaserScan scan = (sensor_msgs::LaserScan)*msg;
   
    static uint32_t seq = 0;
    static sensor_msgs::PointCloud scan3dMsg;
    scan3dMsg.header.seq = seq++;
    scan3dMsg.header.stamp = ros::Time::now();
    scan3dMsg.header.frame_id = "scan_3d";

    static sensor_msgs::ChannelFloat32 channelIntensity; 
    channelIntensity.name = "intensity";
    
    uint16_t pointCount = 0;
    static float iy = 0;      
    
    /*printf( "min angle %6.4lf ", scan.angle_min );
    printf( "max angle %6.4lf ", scan.angle_max );
    printf( "increment %6.4lf ", scan.angle_increment );*/
    for (float theta = scan.angle_min; theta < scan.angle_max; theta += scan.angle_increment)
    {
        geometry_msgs::Point32 point;
        float dis = scan.ranges[pointCount];

        /*point.x = dis * cos(theta) * cos(iy);
        point.y = dis * sin(theta); 
        point.z = dis * cos(theta) * sin(iy);*/
        point.x = dis * cos(theta);
        point.y = dis * sin(theta) * sin(iy); 
        point.z = dis * sin(theta) * cos(iy);
        scan3dMsg.points.push_back(point);
        channelIntensity.values.push_back(scan.intensities[pointCount]);      
        pointCount++;  
    }
    

    iy += (M_PI/180);
    if(iy > M_PI)
    {
        return;
    }
    scan3dMsg.channels.clear();
    scan3dMsg.channels.push_back(channelIntensity);
    scan3d_pub.publish(scan3dMsg);
}


int main (int argc, char **argv)
{
    ros::init(argc, argv, "lidar_transformer");
    ros::NodeHandle n;
    ros::Subscriber scanSubscriber = n.subscribe("/scan", 1000, scanCallback);
    
    scan3d_pub = n.advertise<sensor_msgs::PointCloud>("scan3d", 1000);

    

    ros::Rate loop_rate(10);
    while (ros::ok())
    {

        ros::spinOnce();
        loop_rate.sleep();
    }
	
    return 0;
}
