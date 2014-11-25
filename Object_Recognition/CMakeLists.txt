cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
find_package(OpenCV REQUIRED)

PROJECT(demo) 

set(SRC
	#~ bg_sub.cpp
	#~ tmp.cpp
	demo.cpp
	#~ octree_change_detection)
	)    
add_executable( ${PROJECT_NAME} ${SRC} )
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS})
