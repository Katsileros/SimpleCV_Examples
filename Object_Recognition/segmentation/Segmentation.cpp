#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Segmenter
{
  private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    pcl::PointIndices::Ptr inliers;
  public:
    Segmenter();
    void FillPointCloud(cv::Mat depth_mat);
    void PlaneSegmentation();
    void Visualize(cv::Mat rgb_image);
};

Segmenter::Segmenter()
{
  cloud.reset(new pcl::PointCloud<pcl::PointXYZ>());
  cloud->width = 640;
  cloud->height =480;
  cloud->points.resize (cloud->width * cloud->height);
  
  inliers.reset(new pcl::PointIndices());

}

void Segmenter::FillPointCloud(cv::Mat depth_mat)
{
  float focalLengthX = 575;
  float focalLengthY = 575;
  double centerX = 320.5;
  double centerY = 240.5;
  
  unsigned short depth_value;
  float X,Y,Z;
  for(int i=0;i<depth_mat.rows;i++)
  {  
     for(int j=0;j<depth_mat.cols;j++)
     {
		depth_value = depth_mat.at<unsigned short>(i,j);
		///Z = depth(row, col) / 1000;
		if(depth_value != 0){							//Alliws bgainei synexia to 0,0,0
			Z = float(depth_value)/1000.0f; 
			///X = (col - centerX) * Z / focalLengthX;
			X = (j - centerX) * Z / focalLengthX;
			///Y = (row - centerY) * Z / focalLengthY;
			Y = (i - centerY) * Z / focalLengthY;
		
			cloud->points[i*depth_mat.rows+j].x = X;
			cloud->points[i*depth_mat.rows+j].y = Y;
			cloud->points[i*depth_mat.rows+j].z = Z;
			//Enallaktika:
			//cloud->at(j,i) = pcl::PointXYZ(X,Y,Z);		
			//~ pntCld->push_back(pcl::PointXYZ (X,Y,Z));
		}
     } 	
  }
}

void Segmenter::PlaneSegmentation()
{
  ///Ax+By+Cz+D=0
  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);///A,B,C,D
  ///create the segmentation object
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  ///optional
  seg.setOptimizeCoefficients(true);
  ///mandatory
  seg.setModelType(pcl::SACMODEL_PLANE);
  seg.setMethodType(pcl::SAC_RANSAC);
  seg.setDistanceThreshold (0.01);
  
  seg.setInputCloud(cloud);
  seg.segment(*inliers, *coefficients);    
  
  std::cout<<"Model Coefficients"<< coefficients->values[0] << " " 
                                 << coefficients->values[1] << " "
                                 << coefficients->values[2] << " " 
                                 << coefficients->values[3] << std::endl;
                                 
  std::cerr << "Model inliers: " << inliers->indices.size () << std::endl;
}

void Segmenter::Visualize(cv::Mat rgb_image)
{
	int focalLengthX = 575;
	int focalLengthY = 575;
	double centerX = 320.5;
	double centerY = 240.5;
	int x,y,id;
	
	for(int i=0;i<inliers->indices.size();i++)
	{	
		id = inliers->indices[i];
		if (cloud->points[id].z==0)
		{
			//x = int(focalLengthX*cloud->points[id].x);///x = fx*X;
			//y = int(focalLengthY*cloud->points[id].y);///y = fy*Y;
			//Lathos! An to Z = 0, tote pantote pairnoume to shmeio 0,0,0. Pou antistoixei sto (centerX, centerY). Alla stin ousia
			//apla den exoume pliroforia!
			
		}
		else
		{
			//den ekanes swsto round. To int sou briskei ton amesws mikrotero akeraio. int(1.9) = 1. Giauto evala to +0.5 gia einai san round. Twra feygei olo to trapezi.
			//x = int( centerX + focalLengthX*cloud->points[id].x/cloud->points[id].z + 0.5f);///x = cx + fx*X/Z
			//y = int( centerY + focalLengthY*cloud->points[id].y/cloud->points[id].z + 0.5f);///y = cy + fx*Y/Z
			x = id % cloud->width;
			y = id / cloud->width;
			rgb_image.at<cv::Vec3b>(y,x)[0] = 0;
			rgb_image.at<cv::Vec3b>(y,x)[1] = 0;
			rgb_image.at<cv::Vec3b>(y,x)[2] = 0;
		}
		
		//Efoson ta inliers einai indices, yparxei kai poio aplos tropos:
		//x = id % cloud->width;
		//y = id / cloud->width;
		
		//~ rgb_image.at<cv::Vec3b>(y,x)[0] = 0;
		//~ rgb_image.at<cv::Vec3b>(y,x)[1] = 0;
		//~ rgb_image.at<cv::Vec3b>(y,x)[2] = 0;
	}
	
	cv::imshow("Segmented",rgb_image);
	while(1)
	{
	  if (cv::waitKey(30) == 27) break; ///press Esc to terminate the procedure 	
	}
	
}


int main(int argc, char** argv)
{ 
  ///load images
  cv::Mat rgb, depth;
  rgb = cv::imread("kafes_rgb.png",CV_LOAD_IMAGE_COLOR);
  depth = cv::imread("kafes_depth.png",CV_LOAD_IMAGE_ANYDEPTH);
  
  Segmenter seg;
  seg.FillPointCloud(depth);
  seg.PlaneSegmentation();
  seg.Visualize(rgb);
  return 0;

}

