#include <iostream>
#include <boost/thread/thread.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <pcl/common/common_headers.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/io.h>

class mat2pcl{
	private:
		cv::Mat mat_;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;
	
	public:
		mat2pcl(cv::Mat mat);
		~mat2pcl(){};
		
		pcl::PointCloud<pcl::PointXYZ>::Ptr getPcl(){ return cloud_; }
		void setPcl(cv::Mat mat);
};


