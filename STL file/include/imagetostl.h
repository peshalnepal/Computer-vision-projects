#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;
class ImageToStl
{
public:
    static bool sortbypixels(Mat image1, Mat image2)
    {
        if ((image1.rows * image1.cols) > (image2.rows * image2.cols))
        {
            return true;
        }
        return false;
    }
    vector<Mat> sortimages(vector<Mat> images);
};