#include <pcl/point_types.h>
#include <pcl/features/vfh.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/histogram_visualizer.h>
#include <iostream>

class vfh_features{
	
	private:
		pcl::PointCloud<pcl::VFHSignature308>::Ptr vfhs_;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ ;
  		pcl::PointCloud<pcl::Normal>::Ptr normals_;
	
	public:
		vfh_features(std::string imgFile);
		~vfh_features();
		void vfh_compute();
		//~ pcl::PointCloud<pcl::VFHSignature308>::Ptr get_vfhs(){return vfhs_;};
};
