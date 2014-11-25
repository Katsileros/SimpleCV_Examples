#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/video/background_segm.hpp>
#include <iostream>


int main(int argc, char* argv[])
{	
	cv::Mat rgb, depth;
	rgb = cv::imread("rgb.png");
	depth = cv::imread("depth.png");
	
	cv::namedWindow("rgb");
	//~ cv::namedWindow("depth");
	cv::namedWindow("imgThresholded");
	
	int i=0, j=0;
	
	cv::imshow("rgb",rgb);
	cv::waitKey();
 	
 	unsigned short min = (short(INT_MAX)), max = 0;
	for(i=0;i<480;i++)
	{
		for(j=0;j<640;j++)
		{
			unsigned short depth_value = depth.at<unsigned short>(i, j);
			
			if(depth_value > max)
				max = depth_value;
			if(depth_value < min)
				min = depth_value;
		}
	}
 
	std::cout << "min: " << min << std::endl;
	std::cout << "max: " << max << std::endl;
	
	for(i=0;i<480;i++)
	{
		for(j=0;j<640;j++)
		{
			cv::Vec3b depth_vector = rgb.at<cv::Vec3b>(i, j);
			unsigned short depth_value = depth.at<unsigned short>(i, j);
			
			if((depth_value < 745) || (depth_value > 780))
			{	
				depth_vector.val[0] = 255;
				depth_vector.val[1] = 255;
				depth_vector.val[2] = 255;
				rgb.at<cv::Vec3b>(i, j) = depth_vector;
			}
		}
	}
	
	cv::imshow("rgb",rgb);
	cv::waitKey();
	
	cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowRed = 100;
	int iHighRed = 255;
	
	int iLowGreen = 145; 
	int iHighGreen = 255;
	
	int iLowBlue = 140;
	int iHighBlue = 255;
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowRed", "Control", &iLowRed, 255); //Hue (0 - 179)
	cvCreateTrackbar("HighRed", "Control", &iHighRed, 255);
	
	cvCreateTrackbar("LowGreen", "Control", &iLowGreen, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighGreen", "Control", &iHighGreen, 255);
	
	cvCreateTrackbar("LowBlue", "Control", &iLowBlue, 255); //Value (0 - 255)
	cvCreateTrackbar("HighBlue", "Control", &iHighBlue, 255);
	
	for(;;)
	{       
		cv::Mat imgThresholded;
		inRange(rgb, cv::Scalar(iLowRed, iLowGreen, iLowBlue), cv::Scalar(iHighRed, iHighGreen, iHighBlue), imgThresholded); //Threshold the image
	
		//~ cv::imshow("depth", depth);
		cv::imshow("rgb", rgb);
		cv::imshow("imgThresholded", imgThresholded);
		
		if (cv::waitKey(30) == 27) break; ///press Esc to terminate the procedure
	}
}
