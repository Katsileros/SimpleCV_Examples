#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

/// Global Variables
Mat hsv; Mat hue; 
Mat tracking_img_hsv; Mat tracking_img_hue; 
int bins = 25;

/// Function Headers
void Hist_and_Backproj(int, void* );

/** @function main */
int main( int argc, char** argv )
{
	cv::Mat image;
    cv::VideoCapture cap(0); // open the default camera

	if(!cap.isOpened()) // check if we succeeded
	{
		std::cout << "Cannot open the video file" << std::endl;
		return -1;
	}
	
	int keyPressed = 255;
	
	while(1){
		cap.grab();
		cap.retrieve(image);
			
		  /// Read the image
		  cv::Mat src;
		  src = imread("img1.png", 1 );
		  /// Transform it to HSV
		  cvtColor( src, hsv, CV_BGR2HSV );
		  cvtColor( image, tracking_img_hsv, CV_BGR2HSV );

		  /// Use only the Hue value
		  hue.create( hsv.size(), hsv.depth() );
		  int ch[] = { 0, 0 };
		  mixChannels( &hsv, 1, &hue, 1, ch, 1 );
		  
		  tracking_img_hue.create( tracking_img_hsv.size(), tracking_img_hsv.depth() );
		  mixChannels( &tracking_img_hsv, 1, &tracking_img_hue, 1, ch, 1 );

		  /// Create Trackbar to enter the number of bins
		  namedWindow( "Source image", 1 );
		  createTrackbar("* Hue  bins: ", "Source image", &bins, 180, Hist_and_Backproj );
		  Hist_and_Backproj(0, 0);

		  /// Show the image
		  imshow( "Source image", src );
		  
		  ///Show the tracking image
		  imshow( "Tracking image", image);

		  keyPressed =cv::waitKey(10) & 255;
		  if(keyPressed == 27) //27 is for ESC
			  break;

		}
}


/**
 * @function Hist_and_Backproj
 * @brief Callback to Trackbar
 */
void Hist_and_Backproj(int, void* )
{
//  /* 
  MatND hist;
  int histSize = MAX( bins, 2 );
  float hue_range[] = { 0, 180 };
  const float* ranges = { hue_range };

  /// Get the Histogram and normalize it
  calcHist( &hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
  normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

//*/

  /// Get Backprojection
  MatND backproj;
  calcBackProject( &tracking_img_hue, 1, 0, hist, backproj, &ranges, 1, true );
//  calcBackProject( &tracking_img_hsv, 1, channels, hist, backproj, ranges, 1, true );

  /// Draw the backproj
  imshow( "BackProj", backproj );

// /*
  /// Draw the histogram
  int w = 400; int h = 400;
  int bin_w = cvRound( (double) w / histSize );
  Mat histImg = Mat::zeros( w, h, CV_8UC3 );

  for( int i = 0; i < bins; i ++ )
     { rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 0, 0, 255 ), -1 ); }

  imshow( "Histogram", histImg );
  
//*/

/*
    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( &hsv, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(h*scale, s*scale), Point( (h+1)*scale - 1, (s+1)*scale - 1), Scalar::all(intensity), CV_FILLED );
        }
    
    namedWindow( "H-S Histogram", 1 );
    imshow( "H-S Histogram", histImg );
*/

}

