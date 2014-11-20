cmake_minimum_required(VERSION 2.8.3)
find_package( OpenCV REQUIRED )

PROJECT(bg_sub) 

include_directories(include)
set(SRC
	#~ bg_sub.cpp
	#~ tmp.cpp
	demo.cpp)    
add_executable( ${PROJECT_NAME} ${SRC} )
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS} )
