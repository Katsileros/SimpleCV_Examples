#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"

  /**
    @brief Applies the Sobel edge transform
    @param[in] inImage [const cv::Mat&] Input image in CV_8UC1 format
    @param[out] outImage [cv::Mat*] The processed image in CV_8UC1 format
    @return void
  **/
  void applySobel (const cv::Mat inImage, cv::Mat* outImage)
  {
    //!< appropriate values for scale, delta and ddepth
    int scale = 1;
    int delta = 0; //!< the value for the non-edges
    int ddepth = CV_16S;

    cv::Mat edges;
    inImage.copyTo(edges);
  
    cvtColor( edges, edges, CV_RGB2GRAY );
    //!< Generate grad_x and grad_y
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;

    //!< Gradient X
    cv::Sobel(edges, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_x, abs_grad_x);

    //!< Gradient Y
    cv::Sobel(edges, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_y, abs_grad_y);

    // Total Gradient (approximate)
    cv::Mat grad_g;
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad_g);

    *outImage = grad_g;
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
  
  /**
    @brief Applies the Scharr edge transform
    @param[in] inImage [const cv::Mat&] Input image in CV_8UC1 format
    @param[out] outImage [cv::Mat*] The processed image in CV_8UC1 format
    @return void
   **/
  void applyScharr (const cv::Mat& inImage, cv::Mat* outImage)
  {
   
    //!< appropriate values for scale, delta and ddepth
    int scale = 1;
    int delta = 0; //!< the value for the non-edges
    int ddepth = CV_16S;

    cv::Mat edges;
    inImage.copyTo(edges);
    cvtColor( edges, edges, CV_RGB2GRAY );
    
    //!< Generate grad_x and grad_y
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;

    //!< Gradient X
    cv::Scharr(edges, grad_x, ddepth, 1, 0, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_x, abs_grad_x);

    //!< Gradient Y
    cv::Scharr(edges, grad_y, ddepth, 0, 1, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_y, abs_grad_y);

    // Total Gradient (approximate)
    cv::Mat grad_g;
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad_g);

    *outImage = grad_g;

  }
  
  /**
    @brief Applies the Laplacian edge transform
    @param[in] inImage [const cv::Mat&] Input image in CV_8UC1 format
    @param[out] outImage [cv::Mat*] The processed image in CV_8UC1 format
    @return void
   **/
  void applyLaplacian (const cv::Mat& inImage, cv::Mat* outImage)
  {
    //!< appropriate values for scale, delta and ddepth
    int scale = 1;
    int delta = 0; //!< the value for the non-edges
    int ddepth = CV_16S;

    cv::Mat edges;
    inImage.copyTo(edges);
    cvtColor( edges, edges, CV_RGB2GRAY );
    cv::Laplacian(edges, *outImage, ddepth, 1, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs(*outImage, *outImage);

  }
  
int main()
{
  //!< In this variable the current frame is stored
  cv::Mat frame;
  cv::Mat sobel;
  cv::Mat canny;
  cv::Mat gray;
  cv::Mat scharr;
  cv::Mat laplacian;
  cv::VideoCapture camera(1);
  if ( !camera.isOpened() )  
  {
    std::cout << "Cannot open the video file" << std::endl;
    return -1;
  }
  int KeyPressed=255; 
  int i=0;
  std::cout<<"Press esc if you want to stop the process"<<std::endl;
	std::cout<<"Press s to apply canny"<<std::endl;
  while(1)
  {
    camera.grab();
    camera.retrieve(frame);
    cv::imshow("BGR colorspace",frame);
    
    //!< Apply Sobel edge detections algorithm
    applySobel (frame, &sobel);
    cv::imshow("Sobel algorithm", sobel);
    
    //!< Apply Canny edge detection algorithm
    cvtColor( frame, gray, CV_BGR2GRAY );
    applyCanny( gray, &canny);
    cv::imshow("Canny algorithm",canny);
    
    //!< Apply Scharr edge detection algorithm
    applyScharr (frame, &scharr);
    cv::imshow("Scharr algorithm", scharr);
    
    //!< Apply laplacian edge detection algorithm
    applyLaplacian (frame, &laplacian);
    cv::imshow("Laplacian algorithm", laplacian);
    KeyPressed=cvWaitKey(10) & 255; //!< wait for 'esc' key press for 10 ms
   //!< different choices
    if(KeyPressed==27) //!< KeyPressed==esc
    {
       break;
    }
  }  
}
