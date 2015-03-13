#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"

int main()
{
	
   cv::Mat leftframe;
   cv::Mat rightframe;
  //!< In this variable the current frame is stored
   cv::VideoCapture* rightCameraCapture=new cv::VideoCapture(1);
   cv::VideoCapture* leftCameraCapture=new cv::VideoCapture(2);
   int KeyPressed=255;
   
   if(!leftCameraCapture->isOpened())
    {
       std::cout<<"Left camera is not initialized"<<std::endl;
    }
    if(!rightCameraCapture->isOpened())
    {
       std::cout<<"Right camera is not initialized"<<std::endl;
    }
    
    cv::namedWindow("leftcamera",CV_WINDOW_AUTOSIZE);
	cv::namedWindow("rightcamera",CV_WINDOW_AUTOSIZE);
	
    while(1)
    {
        leftCameraCapture->grab();
        rightCameraCapture->grab();
        leftCameraCapture->retrieve(leftframe);
        rightCameraCapture->retrieve(rightframe);
        
        cv::imshow("leftcamera",leftframe);
        cv::imshow("rightcamera",rightframe);
        KeyPressed=cvWaitKey(10) & 255;
        if(KeyPressed==27) //KeyPressed==esc
        {
            std::cout<<"Ready to exit!!!"<<std::endl;
            break;
        }
        if (KeyPressed==99) //KeyPressed==c
        {
           std::cout<<"save left and right frames snapshot"<<std::endl;
           cv::imwrite( "./left.png", leftframe);
           cv::imwrite( "./right.png",rightframe);
        }
    }
}
