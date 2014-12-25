#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <pcl/common/common_headers.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/sample_consensus/method_types.h>

/**
@class planarSegmentation
@brief Implements the pcl planar_segmentation algorithm
**/
class planarSegmentation
{
	private:
		//!< Private point cloud variable 
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
		//!< Private inliers variable 
		pcl::PointIndices::Ptr inliers;
	
	public:
		//!< Constructor
		planarSegmentation();
		
		//!< Fill the point cloud with the input depth map
		void fillPcd(cv::Mat depth);
		
		//!< Find the inliers of the point cloud
		void segment();
		
		//!< Shows the segmented rgb image
		void visualize(cv::Mat rgb);
		
		//~ //!< Public Xtion Calibration parameteres
	//~ public:
		//~ float focalLengthX;
		//~ float focalLengthY;
		//~ double centerX;
		//~ double centerY;
};
