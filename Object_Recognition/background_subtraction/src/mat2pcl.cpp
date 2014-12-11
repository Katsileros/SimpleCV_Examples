#include "mat2pcl.h"

mat2pcl::mat2pcl(cv::Mat mat)
{	
	//~ std::cout<< "mat.chennels: " << mat.channels() << std::endl;
	this->setPcl(mat);
}

void mat2pcl::setPcl(cv::Mat mat)
{
	int i=0, j=0;
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointXYZ point;
		
	std::vector<cv::Mat> channels;
	cv::split(mat,channels);
	
	for(i=0; i<mat.rows; i++)
	{
		for(j=0; j<mat.cols; j++)
			{
				point.x = channels[0].at<unsigned short>(i, j);
				point.y = channels[1].at<unsigned short>(i, j);
				point.z = channels[2].at<unsigned short>(i, j);
				point_cloud_ptr->points.push_back (point);
			}
	}

	cloud_ = point_cloud_ptr;
}
