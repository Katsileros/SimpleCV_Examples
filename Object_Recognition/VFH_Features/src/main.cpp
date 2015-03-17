#include "vfh_features.h"

int main(int argc, char **argv)
{
	std::cout << "Main execution" << std::endl;
	
	vfh_features *vfh = new vfh_features("apple_1_1_1.pcd");
	vfh->vfh_compute();
	pcl::io::savePCDFileASCII ("0_VFH.pcd", *vfh->getVFH());
	
	// Output datasets
	pcl::PointCloud<pcl::VFHSignature308>::Ptr vfhs (new pcl::PointCloud<pcl::VFHSignature308> ());
	
	if (pcl::io::loadPCDFile("0_VFH.pcd", *vfhs) == -1) //* load the file
	{
		std::cout << ("Couldn't read pcd file \n") << std::endl;
	}
	
	pcl::visualization::PCLHistogramVisualizer 	HistoViewer;
	const std::string id="Visualizing VFH signatures";  	
	HistoViewer.addFeatureHistogram( *vfhs, 50, id, 640, 480);
	HistoViewer.spin();
	
	return 0;
}
