#include "background_subtraction.h"

background_subtraction::background_subtraction()
{
	rgb = cv::imread("rgb.png");
	set_rgb(rgb);
	depth = cv::imread("depth.png");
	set_depth(depth);
	
	thresh = 100;
	max_thresh = 255;
	rng(12345);
	
	this->rm_gb();
	this->threshold_img(rgb);
	
}

void background_subtraction::rm_gb()
{
	int i=0, j=0;
	
	cv::Mat rgb,depth;
	rgb = get_rgb();
	depth = get_depth();
	
	cv::namedWindow("rgb");
	//~ cv::namedWindow("depth");
	
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
 
	//~ std::cout << "min: " << min << std::endl;
	//~ std::cout << "max: " << max << std::endl;
	
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
	
	
	for(i=0;i<480;i++)
	{
		for(j=0;j<640;j++)
		{
			cv::Vec3b rgb_color_vector = rgb.at<cv::Vec3b>(i, j);
			
			if( (rgb_color_vector.val[2] >= 180) || (rgb_color_vector.val[2] <= 30) ) // red
			 //~ || (rgb_color_vector.val[1] >= 80 )  // green
			 //~ || (rgb_color_vector.val[0] >= 70) )// blue
			{
				rgb_color_vector.val[0] = 255; // blue
				rgb_color_vector.val[1] = 255; // green
				rgb_color_vector.val[2] = 255; // red
				//~ //rgb.at<cv::Vec3b>(i, j) = rgb_color_vector;
			}
			
			if( (rgb_color_vector.val[2] >= 90)   // red
			 && (rgb_color_vector.val[1] >= 90)   // green
			 && (rgb_color_vector.val[0] >= 90) ) // blue
			{
				rgb_color_vector.val[0] = 255; // blue
				rgb_color_vector.val[1] = 255; // green
				rgb_color_vector.val[2] = 255; // red
				//~ //rgb.at<cv::Vec3b>(i, j) = rgb_color_vector;
			}
			
			rgb.at<cv::Vec3b>(i, j) = rgb_color_vector;
		
		}
	}
	
	cv::imshow("rgb",rgb);
	cv::waitKey();
	
	//~ return 0;
	
}

void background_subtraction::threshold_img(cv::Mat img)
{	
	set_imgThresholded( img );
	cv::imshow("imgThresholded", imgThresholded);
	cv::waitKey();
	
	//~ /// Create Window
	std::string source_window = "Source";
	cv::namedWindow( source_window, CV_WINDOW_AUTOSIZE );
	cv::imshow( source_window, cv::imread("rgb.png") );
	
	//~ cv::imwrite("imgThresholded.png", imgThresholded);

	cvCreateTrackbar( " Threshold:", "Source", &thresh, max_thresh);
	
	/// Convert image to gray and blur it
	//~ cv::cvtColor( imgThresholded, src_gray, CV_BGR2GRAY );
	//~ cv::blur( src_gray, src_gray, cv::Size(3,3) );
	set_src_gray( imgThresholded );
	cv::cvtColor( src_gray, src_gray, CV_BGR2GRAY );
	cv::blur( src_gray, src_gray, cv::Size(3,3) );
	
	for(;;)
	{
		thresh_callback( 0, 0 );
		if (cv::waitKey() == 27) break; ///press Esc to terminate the procedure
		}
}

void background_subtraction::thresh_callback(int, void* )
{	
	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
  
	int KeyPressed=255;

	/// Detect edges using Threshold
	cv::threshold( get_src_gray(), threshold_output, thresh, 255, cv::THRESH_BINARY );
	/// Find contours
	cv::findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	
	/// Approximate contours to polygons + get bounding rects and circles
	std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
	std::vector<cv::Rect> boundRect( contours.size() );
	std::vector<cv::Point2f>center( contours.size() );
	std::vector<float>radius( contours.size() );
	
	for( int i = 0; i < contours.size(); i++ )
	{  
		cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
		minEnclosingCircle( (cv::Mat)contours_poly[i], center[i], radius[i] );
    }


	/// Draw polygonal contour + bonding rects + circles
	cv::Mat drawing = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	{
       cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       cv::drawContours( drawing, contours_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
       cv::rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
       cv::circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
     }

	/// Show in a window
	cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	for(;;)
	{
		cv::imshow( "Contours", drawing );
		//~ cv::imwrite( "./contours.png", drawing);
	
        if (cv::waitKey() == 27) break; ///press Esc to terminate the procedure
	}
}

