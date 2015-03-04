#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
using namespace cv;

int main(int argc, char** argv)
{

    Mat img = imread("kafes_rgb.png");

    SIFT sift;
    vector<KeyPoint> key_points;

    Mat descriptors;
    sift(img, Mat(), key_points, descriptors);

    Mat output_img;
    drawKeypoints(img, key_points, output_img);

    namedWindow("Image");
    imshow("Image", output_img);
    waitKey(0);
    destroyWindow("Image");

    return 0;
}
