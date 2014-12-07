#ifndef BACKGROUND_SUBTRACTION_H
#define  BACKGROUND_SUBTRACTION_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class BackgroundSubtraction{
	
	private:
		cv::Mat rgb_, depth_;
		cv::Mat imgThresholded_;
		cv::Mat srcGray_;	
	
	public:
		BackgroundSubtraction();
		cv::Mat getRgb(){ return rgb_; }
		cv::Mat getDepth(){ return depth_; }
		cv::Mat getImgThresholded(){ return imgThresholded_; }
		cv::Mat getSrcGray(){ return srcGray_; }
		void setRgb(cv::Mat y){ rgb_ = y; }
		void setDepth(cv::Mat y){ depth_ = y; }
		void setImgThresholded(cv::Mat y){ imgThresholded_ = y; }
		void setSrcGray(cv::Mat y){ srcGray_ = y; }
		
		
		int thresh;
		int maxThresh;
		cv::RNG rng;
		
		
		void rmBG();
		void thresholdImg(cv::Mat img);
		void threshCallback(int, void* );
		
};

#endif
