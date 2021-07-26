#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
Mat originalimg=imread("photos/imagebeforeblur.png");
Mat blurimg;
GaussianBlur(originalimg,blurimg,Size(5,5),5);
cout<<originalimg.size<<endl;
while(true)
    {
    imshow("Original Image",originalimg);
    imshow("Blur Image",blurimg);
    int k =waitKey(0);
    if(k=='s')
        {
        imwrite("../photos/imageafterblur.png",blurimg);
        break;
        }
    }
destroyAllWindows();
return 0;
}
