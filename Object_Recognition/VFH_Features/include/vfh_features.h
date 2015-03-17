#include <pcl/point_types.h>
#include <pcl/features/vfh.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/histogram_visualizer.h>
#include <boost/filesystem.hpp>
#include <iostream>


/**
@class vfh_features
@brief Calculates the VFH descriptor for an object 
**/

class vfh_features{
	
	private:
		//!< The vfh descriptor variable
		pcl::PointCloud<pcl::VFHSignature308>::Ptr vfhs_;
		//!< The input point cloud
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ ;
  		//!< The normals of the given input
  		pcl::PointCloud<pcl::Normal>::Ptr normals_;
	
	public:
		/**
		@brief Constructor
		@param imgFile contains the input point cloud of an object
		**/
		vfh_features(std::string imgFile);
		
		/**
		@brief Destructor
		**/
		~vfh_features();
		
		/**
		@brief Calculate the vfh descriptor of the given object point cloud
		**/
		void vfh_compute();
		
		/**
		@brief Returns the private variable vfhs_
		**/
		pcl::PointCloud<pcl::VFHSignature308>::Ptr getVFH(){return vfhs_;};
};
