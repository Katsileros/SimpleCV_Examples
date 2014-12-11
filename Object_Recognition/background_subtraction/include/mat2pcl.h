#include <iostream>
#include <boost/thread/thread.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <pcl/common/common_headers.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/io.h>


/**
@class mat2pcl
@brief Creates a pcl Pointcloud from a 3-channel input cv::Mat
**/

class mat2pcl{
	private:
		//!< Private variable of the 3-channel cv::Mat
		cv::Mat mat_;
		//!< Private pcl::PointCloud variable produced by the 3-channel cv::Mat
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;
	
	public:
		//!< Constructor
		mat2pcl(cv::Mat mat);
		//!< Destructor
		~mat2pcl(){};
		
		/**
		@brief Returns the private variable cloud_
		@return pcl::PointCloud<pcl::PointXYZ>::Ptr
		**/
		pcl::PointCloud<pcl::PointXYZ>::Ptr getPcl(){ return cloud_; }
		
		/**
		@brief Makes the transformation from the input 3-channels cv::Mat to the pcl::PointCloud
			*  Also it sets the private variable cloud_ to the produces PointCloud
		@return void
		**/
		void setPcl(cv::Mat mat);
};


