cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
find_package(OpenCV REQUIRED)

PROJECT(background_subtraction) 

include_directories(include)

set( SRC src/background_subtraction.cpp
		 src/main.cpp
		 )    
add_executable( ${PROJECT_NAME} ${SRC} )
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS})
