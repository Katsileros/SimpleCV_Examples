#include "mat2pcl.h"

mat2pcl::mat2pcl(cv::Mat mat)
{	
	cv::imshow("mat", mat);
	cv::waitKey();
	
	this->set_pcl(mat);
}

void mat2pcl::set_pcl(cv::Mat mat)
{
	
	int i=0, j=0;
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
	point_cloud_ptr = get_pcl();
	pcl::PointXYZ point;
		
	for(i=0; i<mat.rows; i++)
	{
		for(j=0; j<mat.cols; j++)
			{
				unsigned short depth_value = mat.at<unsigned short>(i, j);
				//~ point.x = 0; //rgb_xyz_vector.val[0];
				//~ point.y = 0; //rgb_xyz_vector.val[1];
				point.z = depth_value;
				//~ std::cout << depth_value << "  ";
				//~ point_cloud_ptr->points.push_back (point);
			}
			//~ std::cout << "\n"<<std::endl;
	}
}
