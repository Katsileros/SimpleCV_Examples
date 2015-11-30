#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/// Global variables
cv::Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;

/// Function header
void cornerHarris_demo( int, void* );

int main()
{
  /// Load source image and convert it to gray
  src = cv::imread( "pattern.png", 1 );
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window and a trackbar
  cv::namedWindow( "Source image", CV_WINDOW_AUTOSIZE );
  cv::createTrackbar( "Threshold: ", "Source image", &thresh, max_thresh, cornerHarris_demo );
  cv::imshow( "Source image", src );

  cornerHarris_demo( 0, 0 );

  cv::waitKey(0);
  return(0);
}

/** @function cornerHarris_demo */
void cornerHarris_demo( int, void* )
{

  cv::Mat dst, dst_norm, dst_norm_scaled;
  dst = cv::Mat::zeros( src.size(), CV_32FC1 );
  cv::Mat copy;
  copy = src_gray.clone();
  /// Detecting corners
  cv::cornerHarris( copy, dst, 2, 3, 0.04, cv::BORDER_DEFAULT );
  
  /// Normalizing
  normalize( dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
  { 
    for( int i = 0; i < dst_norm.cols; i++ )
    {
      if( (int) dst_norm.at<float>(j,i) > thresh )
      {
       circle( copy, cv::Point( i, j ), 5,  cv::Scalar(0,0,255), -1, 8, 0 );
      }
    }
  }
  /// Showing the result
  cv::namedWindow( "Source image", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Source image", copy);
}
