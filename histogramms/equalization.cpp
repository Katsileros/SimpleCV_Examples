#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

void show_histogramm(std::string const& name, cv::Mat1b const& image)
{
  std::cout<<"Pethana";
  /// Set histogram bins count
  int bins = 256;
  int histSize[] = {bins};
  /// Set ranges for histogram bins
  float lranges[] = {0, 256};
  const float* ranges[] = {lranges};
  /// create matrix for histogram
  cv::Mat hist;
  int channels[] = {0};
  
  /// create matrix for histogram visualization
  int const hist_height = 256;
  cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

  cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

  double max_val=0;
  minMaxLoc(hist, 0, &max_val);

  // visualize each bin
  for(int b = 0; b < bins; b++) 
  {
    float const binVal = hist.at<float>(b);
    int   const height = cvRound(binVal*hist_height/max_val);
    cv::line(hist_image
        , cv::Point(b, hist_height-height), cv::Point(b, hist_height)
        , cv::Scalar::all(255));
  }
    cv::imshow(name, hist_image);
}
int main( int argc, char** argv )
{
  cv::Mat1b src, dst;
  /// Load image
  src = cv::imread("LenaDark.png", 1 );
  if( !src.data )
      return -1;

  /// Apply Histogram Equalization
  cv::equalizeHist( src, dst );

  /// Display results
  cv::imshow( "Source image", src );
  show_histogramm("Source hist", src);
  cv::imshow( "Equalized Image", dst );
  show_histogramm("Equalized hist", dst);
  /// Wait until user exits the program
  cv::waitKey(0);

  return 0;
}
