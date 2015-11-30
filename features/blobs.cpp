#include <iostream>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

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

int main()
{
  //!< In this variable the current frame is stored
  cv::Mat frame;
  cv::VideoCapture camera(1);
  if ( !camera.isOpened() )  
  {
    std::cout << "Cannot open the video file" << std::endl;
    return -1;
  }
  while(1)
  {
    camera.grab();
    camera.retrieve(frame);
    cv::Mat blobs=cv::Mat::zeros(480,640,CV_8UC1);
    blobDetect(frame, &blobs);
    cv::imshow("Current frame", frame);
    cv::imshow("Blobs frame", blobs);
    cv::waitKey(10);
  }  
}
