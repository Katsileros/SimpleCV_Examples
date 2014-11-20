#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/video/background_segm.hpp>
#include <iostream>


int main(int argc, char* argv[])
{	
	cv::Mat rgb, depth;
	rgb = cv::imread("learn0.png");
	depth = cv::imread("disp_learn0.png");
	
	//~ cv::namedWindow("rgb");
	//~ cv::namedWindow("depth");
	
	int iLowH = 0;
	int iHighH = 255;
	
	int iLowS = 0; 
	int iHighS = 255;
	
	int iLowV = 0;
	int iHighV = 255;
	
	cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);
	
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
	
	
	while (true)
    {

	cv::Mat imgHSV;

	cvtColor(rgb, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	cv::Mat imgThresholded;

	inRange(rgb, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
		  
	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
	dilate( imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 

	//morphological closing (fill small holes in the foreground)
	dilate( imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 
	erode(imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

	imshow("Thresholded Image", imgThresholded); //show the thresholded image
	imshow("Original", rgb); //show the original image

        if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            std::cout << "esc key is pressed by user" << std::endl;
            break; 
       }
	}
	
	
	
/*	
	int i=0, j=0;
	
	//~ std::cout << "depth.rows:" << depth.rows << std::endl;
	//~ std::cout << "depth.cols:" << depth.cols << std::endl;
 	
 	//~ unsigned short depth_value = depth.at<unsigned short>(280, 320);
 	//~ std::cout<< depth_value ;
 	
 	double min, max;
	cv::minMaxLoc(rgb, &min, &max);
	

 
 
 
	int threshold_r, threshold_g, threshold_b, span;
	threshold_r = 185;
	threshold_g = 185;
	threshold_b = 185;
	span = 45;
 	
	for(i=0;i<480;i++)
	{
		for(j=0;j<640;j++)
		{
			cv::Vec3b rgb_color_vector = rgb.at<cv::Vec3b>(i, j);
			unsigned short depth_value = depth.at<unsigned short>(i, j);
			

			if( (rgb_color_vector.val[0] > threshold_b  && rgb_color_vector.val[0] < threshold_b + span) 
			 || (rgb_color_vector.val[1] > threshold_g  && rgb_color_vector.val[1] < threshold_g + span) 
			 || (rgb_color_vector.val[2] > threshold_r  && rgb_color_vector.val[2] < threshold_r + span) )
			 {
				//~ if((depth_value < 25) || (depth_value > 1029)){
						//~ std::cout << "depth: " << depth_value << std::endl;
						rgb_color_vector.val[0] = max;
						rgb_color_vector.val[1] = max;
						rgb_color_vector.val[2] = max;
				//~ }
		}
			rgb.at<cv::Vec3b>(i, j) = rgb_color_vector;
			
		}
	}
	
*/	
	//~ for(;;)
	//~ {
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

            //~ cv::imshow("depth", depth);
			//~ cv::imshow("rgb", rgb);
		
		//~ if (cv::waitKey(30) == 27) break; ///press Esc to terminate the procedure
	//~ }
}
