#include "vfh_features.h"

int main(int argc, char **argv)
{
	std::cout << "Main execution" << std::endl;
	
	vfh_features *vfh = new vfh_features("apple_1_1_1.pcd");
	vfh->vfh_compute();
	
	return 0;
}
