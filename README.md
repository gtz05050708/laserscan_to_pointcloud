# laserscan_to_pointcloud
This is a ROS progam that transforms the 2D laser data generated from a RPlidar A2 to a 3D point cloud. The transformation is done through transforming 2D coordinate to a 3D one using coordinate on a third axis acquired by rotating the lidar.

# To Run
Place the repository within catkin workspace and run the Make file to compile. 
Run launch file to generate 3d point cloud from the lidar and save it as a pcd format.

# Hardware
The lidar used is a RPlidar A2, and it is mounted on a custom hardware platform for rotating the lidar. Rplidar's ROS package is used to acquire data from the lidar. The package is available on Github at https://github.com/robopeak/rplidar_ros 

# Example Results
![SRC Presentation](https://user-images.githubusercontent.com/44013817/174145752-f8d0ce8a-45e5-4aea-8836-ae5d1f65de9d.png)
Further examples see /examples.
