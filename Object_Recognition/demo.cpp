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
	

	
	//~ for(i=0;i<480;i++)
	//~ {
		//~ for(j=0;j<640;j++)
		//~ {
			//~ cv::Vec3b rgb_color_vector = rgb.at<cv::Vec3b>(i, j);
			//~ if( (rgb_color_vector.val[2] < 85 || rgb_color_vector.val[0] > 110)  // red
			 //~ && (rgb_color_vector.val[1] < 85 || rgb_color_vector.val[1] > 105)  // green
			 //~ && (rgb_color_vector.val[0] < 85 || rgb_color_vector.val[0] > 105) )// blue
			//~ {
				//~ rgb_color_vector.val[0] = 255; // blue
				//~ rgb_color_vector.val[1] = 255; // green
				//~ rgb_color_vector.val[2] = 255; // red
			//~ }
				//~ rgb.at<cv::Vec3b>(i, j) = rgb_color_vector;
		//~ }
	//~ }
	
	
	for(;;)
	{
            /*
            pros stigmh autos o kwdikas se endiaferei.
            To depth periexei to vathos, to rgb to xrwma.
            H eikona tou xtion einai 640x480 pixels. An to deis san pinaka, einai 480 rows, 640 columns.
            To stoixeio (0,0) tou pinaka autou (dil. tis eikonas) einai to panw deksia.

            Sou deixnw ena paradeigma pws blepoume ta stoixeia twn pinakwn autwn:
            estw oti theloume na doume to pixel sth thesh row=10, col=20.

            int row = 10;
            int col = 20;
            unsigned short depth_value = depth.at<unsigned short>(10, 20);
            cv::Vec3b rgb_color_vector = rgb.at<cv::Vec3b>(10, 20);
            int blue = rgb_color_vector.val[0];
            int green = rgb_color_vector.val[1];
            int red = rgb_color_vector.val[2];

            Profanws tha exeis polles apories, de kserw kai kata poso ksereis c++.
            An den ksereis ti einai to unsigned short, des to sto google.
            me tin entolh ".at< >" blepoume ena sygekrimeno stoixeio tou pinaka. Auto to stoixeio einai metablith typou pou brisketai
            mesa sta < >. To depth periexei metablites unsigned short, enw to rgb periexei Vec3b.
            To Vec3b einai ena dianisma (vector) apo 3 bytes. to kathe byte einai ena xrwma. Sto kwdika fainetai pws mporeis na ta diavaseis.

            Gia prwto peirama mporeis na pareis mia eikona kai na ektypwseis ola ta pixels gia na deis tis times tous. To depth
            einai se milimeters, epomenws ena antikeimeno sto 1m tha exei timh 1000.

            */
            
            cv::Mat imgThresholded;
			inRange(rgb, cv::Scalar(iLowRed, iLowGreen, iLowBlue), cv::Scalar(iHighRed, iHighGreen, iHighBlue), imgThresholded); //Threshold the image

            //~ cv::imshow("depth", depth);
			cv::imshow("rgb", rgb);
			cv::imshow("imgThresholded", imgThresholded);
		
		if (cv::waitKey(30) == 27) break; ///press Esc to terminate the procedure
	}
}
