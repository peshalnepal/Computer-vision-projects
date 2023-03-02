#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
using namespace std;
using namespace cv;
class SurfDetector
{
public:
    tuple<vector<KeyPoint>, Mat> featuresdetect(Mat image);
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

private:
    Mat IntegralImages(Mat images);
    Mat verticalfilterforimage(Mat integratedimage, int size, int scale);
    Mat Horizontalfilterforimage(Mat integratedimage, int size, int scale);
    Mat Daigonalfilterforimage(Mat integratedimage, int size, int scale);
    Mat createMat3Drix(Mat imagearray[3], int x, int y);
    vector<vector<Mat>> createfilteredimage(Mat integratedimage, int scale, int octave);
    tuple<Mat, Mat> calculatehaarwavelets(Mat image, int nooftimes, int size);
    Mat descriptors(Mat initial_image, vector<KeyPoint> keypoints);
    float *calculatewaveletsdescriptor(Mat image, int size, int x, int y);
    vector<KeyPoint> calculateorientation(Mat image, vector<KeyPoint> keypoints);
    vector<KeyPoint> removekeypoints(vector<KeyPoint> keypointvect);
};