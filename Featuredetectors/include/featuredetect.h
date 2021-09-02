#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include <vector>
#include<opencv2/xfeatures2d.hpp>
#include <cmath>
using namespace std;
using namespace cv;

class FeatrueDetect
{
    public:
    vector<KeyPoint> featuresdetect(Mat image);
    private:
    Mat createMat3Drix(Mat imagearray[3],int x,int y);
    vector<float> descripter(Mat image,int x,int y);
    vector<KeyPoint> sortkeypoints(vector<KeyPoint> keypointvect);
    vector<float> calculatesigmavalue(float sigma,int number_of_intervals);
    vector<vector<Mat>> createblurimage(Mat image,float sigma, int num_intervals,int octave);
    // Mat convolution_image(Mat image,Mat filter_);
    // Mat Gaussian_blur(Mat image,int ksize,float std);
};