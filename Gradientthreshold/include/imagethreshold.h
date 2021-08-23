#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
class ImageThreshold
{
  public:
  ImageThreshold();
  Mat sobelfilter(Mat image,int x,int y);
  Mat Gaussian_blur(Mat image,int ksize,float std);
  Mat thresholding(Mat image,int threshold);
  private:
  Mat convolution_image(Mat image,Mat filter_);
};