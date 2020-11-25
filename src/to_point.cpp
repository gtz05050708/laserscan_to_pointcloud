#include <ros/ros.h>

#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Point32.h"
#include "sensor_msgs/ChannelFloat32.h"
#include "std_msgs/String.h"

#include "std_msgs/Float32.h"
#include "std_msgs/UInt16.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>


ros::Publisher scan3d_pub;
ros::Publisher angle_pub;

const int INITIAL_ANGLE = 235;
const int MAX_ANGLE = 55;
int servo_angle = INITIAL_ANGLE;

void saveCloud(sensor_msgs::PointCloud &pointcloud) {
    pcl::PointCloud<pcl::PointXYZI> cloud;
    cloud.height = 1;
    cloud.width = pointcloud.points.size();
    cloud.is_dense = false;
    cloud.points.resize(cloud.width * cloud.height);
    for (size_t i = 0; i < cloud.points.size(); i++) {
        cloud.points[i].x = pointcloud.points[i].x;
        cloud.points[i].y = pointcloud.points[i].y;
        cloud.points[i].z = pointcloud.points[i].z;
        cloud.points[i].intensity = pointcloud.channels[0].values[i];

    }
    pcl::io::savePCDFileBinary("/home/david/catkin_ws/src/scan_to_point/src/points.pcd", cloud);
}

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{

    //static bool angle_change = true;
    sensor_msgs::LaserScan scan = (sensor_msgs::LaserScan)*msg;
   
    static int seq = 0;
    static sensor_msgs::PointCloud pointcloud;
    static std_msgs::String angle_msg;
    pointcloud.header.seq = seq++;
    pointcloud.header.stamp = ros::Time::now();
    pointcloud.header.frame_id = "cloudframe";

    static sensor_msgs::ChannelFloat32 channelIntensity; 
    channelIntensity.name = "intensity";
    
    uint16_t pointCount = 0;     
    float phi = 55 + 180 - servo_angle;
    phi = phi / 180 * M_PI;
    
    if (servo_angle < MAX_ANGLE) {
        angle_msg.data = std::to_string(INITIAL_ANGLE);
        angle_pub.publish(angle_msg);
        saveCloud(pointcloud);
        ros::shutdown();
    }
    
    for (float theta = scan.angle_min; theta < scan.angle_max; theta += scan.angle_increment)
    {
        geometry_msgs::Point32 point;
        float dis = scan.ranges[pointCount];

        point.x = dis * cos(theta);
        point.y = dis * sin(theta) * sin(phi); 
        point.z = dis * sin(theta) * cos(phi);
        pointcloud.points.push_back(point);
        channelIntensity.values.push_back(scan.intensities[pointCount]);    
        pointCount++;  
    }
    
    //angle_change = !angle_change;
    //if (angle_change) {
    servo_angle--;
    //}
    angle_msg.data = std::to_string(servo_angle);
    angle_pub.publish(angle_msg);

    pointcloud.channels.clear();
    pointcloud.channels.push_back(channelIntensity);
    scan3d_pub.publish(pointcloud);
}



int main (int argc, char **argv)
{
    ros::init(argc, argv, "transformer");
    ros::NodeHandle n;
    ros::Subscriber scanSubscriber = n.subscribe("/scan", 1000, scanCallback);
    scan3d_pub = n.advertise<sensor_msgs::PointCloud>("scan3d", 1000);
    angle_pub = n.advertise<std_msgs::String>("angle", 1000);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
	
    return 0;
}
