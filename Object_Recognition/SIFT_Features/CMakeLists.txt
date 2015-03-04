cmake_minimum_required(VERSION 2.8.3)
find_package( OpenCV REQUIRED )

PROJECT(sift) 

include_directories(include)
set(SRC sift.cpp)
add_executable( ${PROJECT_NAME} ${SRC} )
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS} )
