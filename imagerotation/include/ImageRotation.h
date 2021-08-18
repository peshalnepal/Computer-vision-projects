#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<math.h>
using namespace std;
using namespace cv;
class ImageRotation
{
public:
    ImageRotation();
    Mat imagerotationalgorithm(Mat image,int angle,bool clockwise);
private:
    float pi = 2 * acos(0);
    float radianangle ;
    int x,y;
    bool rotationdirection;
    int* getoutputwidthheight();
};
