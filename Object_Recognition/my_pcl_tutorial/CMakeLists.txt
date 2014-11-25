cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project( octree_change_detection )

find_package( PCL 1.2 REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package( OpenCV REQUIRED )
add_executable( octree_change_detection octree_change_detection.cpp )
target_link_libraries( octree_change_detection ${OpenCV_LIBS} ${PCL_LIBRARIES})

