#include "BackgroundSubtraction.h"
#include "planarSegmentation.h"

int main(int argc, char **argv)
{
	BackgroundSubtraction *bg_sub = new  BackgroundSubtraction();
	
	bg_sub->setRgb(cv::imread("kafes_rgb.png"));
	bg_sub->setDepth(cv::imread("kafes_depth.png"));
	
	planarSegmentation seg;
	seg.fillPcd(bg_sub->getDepth());
	seg.segment();
	seg.visualize(bg_sub->getRgb());
	
	//~ bg_sub->removeBackGround();
	//~ std::cout<< "\nFinished removeBackground." << std::endl;
	//~ cv::waitKey();
	//~ bg_sub->thresholdImg(bg_sub->getRgb());
	//~ std::cout<< "\nFinished boundingBox." << std::endl;
	//~ cv::waitKey();
	
	return 0;
}
