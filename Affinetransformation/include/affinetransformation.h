
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
class AffineTransformation
{
    public:
    AffineTransformation();
    Mat applytranslation(Mat image,int x_,int y_);
    Mat applyrotation(Mat image,float angle);
    Mat applyshear(Mat image,float x_,float y_);
    private:
    int* multiplication(Mat matrix_1,Mat matrix_2);
    int* finalwidthheight(int x_,int y_,float angle);
};