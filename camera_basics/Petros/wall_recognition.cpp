#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv.h"
#include <string>
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/features2d/features2d.hpp>

/// Global Variables
cv::Mat hsv[7]; 
cv::Mat tracking_img_hsv; 
cv::Mat src[7];
int bins = 25;


void applyCanny(const cv::Mat& inImage, cv::Mat* outImage);
void blobDetect(cv::Mat srcimage, cv::Mat* out);

/**
 * @function Hist_and_Backproj
 * @brief Callback to Trackbar
 */
void Hist_and_Backproj(int, void* )
{

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
    cv::MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( hsv, 7, channels, cv::Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    cv::Mat histImg = cv::Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, cv::Point(h*scale, s*scale), cv::Point( (h+1)*scale - 1, (s+1)*scale - 1), cv::Scalar::all(intensity), CV_FILLED );
        }
    
    cv::namedWindow( "H-S Histogram", 1 );
    imshow( "H-S Histogram", histImg );



  /// Get Backprojection
  cv::MatND backproj;
  calcBackProject( &tracking_img_hsv, 1, channels, hist, backproj, ranges, 1, true );

  /// Draw the backproj
  imshow( "BackProj", backproj );
  
  cv::Mat canny;
  ///Apply edge detection with Canny algorithm
  applyCanny(backproj,&canny);
  imshow("Canny-edges: ", canny);
  
  ///Apply blob detection
  cv::Mat blobs=cv::Mat::zeros(480,640,CV_8UC1);
  blobDetect(canny, &blobs);
  cv::imshow("Blobs ", blobs);
	
}


 /**
    @brief Applies the Canny edge transform
    @param[in] inImage [const cv::Mat&] Input image in CV_8UC1 format
    @param[out] outImage [cv::Mat*] The processed image in CV_8UC1 format
    @return void
  **/
  void applyCanny(const cv::Mat& inImage, cv::Mat* outImage)
  {
    inImage.copyTo(*outImage);
    cv::Mat detected_edges;
    cv::Mat dst;
    int ratio = 3;
    int kernel_size = 3;
    int lowThreshold = 100;

    //!< Reduce noise with a kernel 3x3
    cv::blur(*outImage, detected_edges, cv::Size(kernel_size, kernel_size));

    //!< Canny detector
    cv::Canny(detected_edges, detected_edges, lowThreshold,
        lowThreshold * ratio, kernel_size);

    //!< Using Canny's output as a mask, we display our result
    dst = cv::Scalar::all(0);

    outImage->copyTo(dst, detected_edges);
    *outImage = dst; 

 }
 
std::vector<cv::KeyPoint> keyPoints;
void blobDetect(cv::Mat srcimage, cv::Mat* out)
{
  cv::Mat circularBlobs;
 
  std::vector< std::vector <cv::Point> > contours;
  std::vector< std::vector <cv::Point> > approxContours;

  cv::SimpleBlobDetector::Params params;
  params.minThreshold = 40;
  params.maxThreshold = 60;
  params.thresholdStep = 5;

  params.minArea = 550;
  params.minConvexity = 0.6;
  params.minInertiaRatio = 0.5;

  params.maxArea = 8000;
  params.maxConvexity = 10;
  params.maxCircularity=1;
  params.minCircularity=0.3;

  params.filterByColor = false;
  params.filterByCircularity = true;
 
  cv::SimpleBlobDetector blobDetector( params );
  blobDetector.create("SimpleBlob");

  blobDetector.detect( srcimage, keyPoints );
        //blobDetector.detectEx( src, keyPoints, contours );
  cv::drawKeypoints( srcimage, keyPoints, *out, CV_RGB(0,255,255), cv::DrawMatchesFlags::DEFAULT);
  approxContours.resize( contours.size() );

  for( int i = 0; i < contours.size(); ++i )
  {
    cv::approxPolyDP( cv::Mat(contours[i]), approxContours[i], 4, 1 );
    cv::drawContours( *out, contours, i, CV_RGB(255,0,255));
    cv::drawContours( *out, approxContours, i, CV_RGB(255,0,255));
  }
}
 
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
	int ch[] = { 0, 0 };
	
	while(1){
		cap.grab();
		cap.retrieve(image);
			
		  /// Read the image
		  
		  for(int i=0; i<7; i++){
			src[i] = cv::imread(cv::format("%d.png",i), 1 );
			
			/// Transform it to HSV
			cvtColor( src[i], hsv[i], CV_BGR2HSV );
		  }
		  
		  /// Transform tracking image to HSV
		  cvtColor( image, tracking_img_hsv, CV_BGR2HSV );

		  /// Hist and Backprojection function call
		  Hist_and_Backproj(0, 0);
		  
		  ///Show the tracking image
		  imshow( "Tracking image", image);
		 
		  keyPressed =cv::waitKey(10) & 255;
		  if(keyPressed == 27) //27 is for ESC
			  break;

		}
		
}
 
