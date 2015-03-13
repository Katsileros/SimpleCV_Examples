cmake_minimum_required(VERSION 2.8.3)
find_package( OpenCV REQUIRED )

PROJECT(tmp-camera) 

include_directories(include)
set(SRC
	camera.cpp)    
add_executable( ${PROJECT_NAME} ${SRC} )
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS} )
