#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
#include <limits>
#include <random>
#include <utility>
using namespace std;
using namespace cv;
class Orbfeaturedetector
{
public:
    Orbfeaturedetector(int totalkeypoints);
    int keypointdisplay;
    tuple<vector<KeyPoint>, Mat> featuresdetect(Mat image);
    static bool sortResponse(KeyPoint &firstkeypoint, KeyPoint &secondkeypoint)
    {
        if (firstkeypoint.response > secondkeypoint.response)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
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
    vector<Mat> scalespace(Mat image, int scalingfactor);
    vector<KeyPoint> calculateorientation(vector<KeyPoint> keypoints, vector<Mat> scaledimages);
    Mat descriptors(vector<KeyPoint> keypoints, vector<Mat> scaledimages, int seedvalue);
    vector<KeyPoint> removekeypoints(vector<KeyPoint> keypointvect);
    vector<KeyPoint> Removekeypoint(vector<KeyPoint> keypoints, int numberofkeypoints);
};