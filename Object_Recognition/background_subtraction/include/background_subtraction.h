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

class background_subtraction{
	
	private:
		cv::Mat rgb, depth;
		cv::Mat imgThresholded;
		cv::Mat src_gray;	
	
	public:
		background_subtraction();
		cv::Mat get_rgb(){ return rgb; }
		cv::Mat get_depth(){ return depth; }
		cv::Mat get_imgThresholded(){ return imgThresholded; }
		cv::Mat get_src_gray(){ return src_gray; }
		void set_rgb(cv::Mat y){ rgb = y; }
		void set_depth(cv::Mat y){ depth = y; }
		void set_imgThresholded(cv::Mat y){ imgThresholded = y; }
		void set_src_gray(cv::Mat y){ src_gray = y; }
		
		
		int thresh;
		int max_thresh;
		cv::RNG rng;
		
		
		void rm_gb();
		void threshold_img(cv::Mat img);
		void thresh_callback(int, void* );
		
};

#endif
