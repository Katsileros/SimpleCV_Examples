#include "vfh_features.h"

typedef std::pair<std::string, std::vector<float> > vfh_model;

vfh_features::vfh_features(std::string imgFile)
{
  std::cout << "Vfh constructor" << std::endl;
  
  cloud_.reset(new pcl::PointCloud<pcl::PointXYZ>());
  normals_.reset(new pcl::PointCloud<pcl::Normal> ());
  vfhs_.reset(new pcl::PointCloud<pcl::VFHSignature308> ());
  
  if (pcl::io::loadPCDFile(imgFile, *cloud_) == -1) //* load the file
  {
    std::cout << ("Couldn't read pcd file \n") << std::endl;
  }
  
}

void vfh_features::vfh_compute()
{		
  // Estimate the normals.
  pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
  normalEstimation.setInputCloud(cloud_);
  normalEstimation.setRadiusSearch(0.03);
  pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
  normalEstimation.setSearchMethod(kdtree);
  normalEstimation.compute(*normals_);
 
  // VFH estimation object.
  pcl::VFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignature308> vfh;
  vfh.setInputCloud(cloud_);
  vfh.setInputNormals(normals_);
  vfh.setSearchMethod(kdtree);
  // Optionally, we can normalize the bins of the resulting histogram,
  // using the total number of points.
  vfh.setNormalizeBins(true);
  // Also, we can normalize the SDC with the maximum size found between
  // the centroid and any of the cluster's points.
  vfh.setNormalizeDistance(false);
  
  vfh.compute(*vfhs_);
  
  //~ std::cout << "Found   " << vfhs_->points.size() << " features. " << std::endl;
  //~ std::cout << "vfh " << *vfhs_ <<std::endl;
	
  //~ pcl::visualization::PCLHistogramVisualizer 	HistoViewer;
  //~ const std::string id="Visualizing VFH signatures";  	
  //~ HistoViewer.addFeatureHistogram( *vfhs_, 50, id, 640, 480);
  //~ HistoViewer.spin();
}
