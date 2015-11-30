#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"

int main()
{
  //!< In this variable the current frame is stored
  cv::Mat frame;
  cv::Mat gray;
  cv::Mat hsv;
  
  cv::VideoCapture camera(1);
  if ( !camera.isOpened() )  
  {
    std::cout << "Cannot open the video file" << std::endl;
    return -1;
  }
  int KeyPressed=255; 
  int i=0;
  std::cout<<"Press esc if you want to stop the process"<<std::endl;
	std::cout<<"Press s to save snapshot"<<std::endl;
  while(1)
  {
    camera.grab();
    camera.retrieve(frame);
    cv::cvtColor(frame,gray,CV_BGR2GRAY);
    cv::imshow("BGR colorspace",frame);
    cv::imshow("GRAY colorspace",gray);
    KeyPressed=cvWaitKey(10) & 255; //!< wait for 'esc' key press for 10 ms
   //!< different choices
    if(KeyPressed==27) //!< KeyPressed==esc
    {
       break;
    }
    if(KeyPressed==115) //!< KeyPressed==s
    {
     char temp_name[50];
	 sprintf(temp_name,"xx%d.png",i+1);
     std::string path="/home/katsi/Documents/myCalibrationCameraFiles";
     std::string name=path+temp_name;
     cv::imwrite(name,frame);
     std::cout<<"Image "<<temp_name<<" saved"<<std::endl;
     i++;
    }
      
  }  
}
