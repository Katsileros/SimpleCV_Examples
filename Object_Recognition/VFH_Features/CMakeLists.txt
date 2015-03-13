cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

PROJECT(VFH_Features)

find_package( OpenCV REQUIRED )
find_package( PCL 1.7 REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(include)

set( SRC src/vfh_features.cpp
		 src/main.cpp
		 )    
add_executable( ${PROJECT_NAME} ${SRC} )
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS})
target_link_libraries( ${PROJECT_NAME}  ${OpenCV_LIBS} ${PCL_LIBRARIES})

