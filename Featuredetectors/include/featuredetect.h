#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
using namespace std;
using namespace cv;

class FeatrueDetect
{
public:
    static bool sortkeypoint(KeyPoint &firstkeypoint, KeyPoint &secondkeypoint)
    {
        if (firstkeypoint.pt.x < secondkeypoint.pt.x)
        {
            return true;
        }
        else if (firstkeypoint.pt.x == secondkeypoint.pt.x && firstkeypoint.pt.y < secondkeypoint.pt.y)
        {
            return true;
        }
        else if (firstkeypoint.pt == secondkeypoint.pt && firstkeypoint.angle < secondkeypoint.angle)
        {
            return true;
        }
        else if (firstkeypoint.pt == secondkeypoint.pt && firstkeypoint.angle == secondkeypoint.angle && firstkeypoint.response < secondkeypoint.response)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    tuple<vector<KeyPoint>, Mat> featuresdetect(Mat image);

private:
    Mat createMat3Drix(Mat imagearray[3], int x, int y);
    vector<KeyPoint> removekeypoints(vector<KeyPoint> keypointvect);
    vector<KeyPoint> sortkeypoints(vector<KeyPoint> keypointvect);
    vector<float> calculatesigmavalue(float sigma, int number_of_intervals);
    vector<vector<Mat>> createblurimage(Mat image, float sigma, int num_intervals, int octave);
    Mat create_descripter(vector<KeyPoint> keypoints_, vector<vector<Mat>> imagevec);
    vector<vector<Mat>> DifferenceofGaussianimg(vector<vector<Mat>> blurredimage);
    vector<KeyPoint> calculateorientation(vector<KeyPoint> keypoints, vector<vector<Mat>> imagevec_cpy);

    // Mat convolution_image(Mat image,Mat filter_);
    // Mat Gaussian_blur(Mat image,int ksize,float std);
};