# laserscan_to_pointcloud
This is a ROS progam that transforms the 2D laser data generated from a RPlidar A2 to a 3D point cloud. The transformation is done through transforming 2D coordinate to a 3D one using coordinate on a third axis acquired by rotating the lidar.

# To Run
Place the repository within catkin workspace and run the Make file to compile. 
Run launch file to generate 3d point cloud from the lidar and save it as a pcd format.

# Hardware
The lidar used is a RPlidar A2, and it is mounted on a custom hardware platform for rotating the lidar. Rplidar's ROS package is used to acquire data from the lidar. The package is available on Github at https://github.com/robopeak/rplidar_ros 

# Example Results
![Screenshot from 2020-08-12 18-07-19](https://user-images.githubusercontent.com/44013817/174145590-022cda15-54f0-413d-aaf0-0149b0fd752f.png)
![example_real](https://user-images.githubusercontent.com/44013817/174145674-b3d48435-1308-4461-971f-9c0072832718.jpg)
