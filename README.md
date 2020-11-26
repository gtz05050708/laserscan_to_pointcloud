# laserscan_to_pointcloud
This is a ROS progam that transforms the 2D laser data generated from a RPlidar A2 to a 3D point cloud. The transformation is done through transforming 2D coordinate to a 3D one using coordinate on a third axis acquired by rotating the lidar.

# To Run
Place the repository within catkin workspace and run the Make file to compile. 
Run scan_to_point to generate 3d point cloud from the lidar and save it as a ply format.
