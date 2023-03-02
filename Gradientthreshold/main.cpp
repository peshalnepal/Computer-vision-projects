#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include"include/imagethreshold.h"
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
string path;
Mat originalimage;
       try
       {
        if (argc==1)
            {
                path="photos/check.png";
            }
        if(argc >=2)
            {
                path=argv[1];
            }
        originalimage=imread(path,IMREAD_GRAYSCALE);
        if(originalimage.empty())
           {
               throw("image not found in the path");
           }
       }
       catch(const char* msg)
       {
          cerr << msg << '\n';
          return 0;
       }

Mat blurimage=originalimage.clone();
Mat imagethreshold1,imagethreshold2,imagethreshold3;
ImageThreshold imgthreshold;
Mat image;
cout<<blurimage.rows<<","<<blurimage.cols<<endl;
blurimage=imgthreshold.Gaussian_blur(blurimage,5,5);
image=imgthreshold.sobelfilter(blurimage,1,1);
imagethreshold1=imgthreshold.thresholding(image,200);
imagethreshold2=imgthreshold.thresholding(image,150);
imagethreshold3=imgthreshold.thresholding(image,100);
while(true)
{
    imshow("show image",originalimage);
    // imshow("show Gaussian blur result",blurimage);
    // imshow("show sobel filter result",image);
    imshow("show threshold 200 result",imagethreshold1);
    imshow("show threshold 150 result",imagethreshold2);
    imshow("show threshold 100 result",imagethreshold3);
    int k=waitKey(0);
    if(k==27)
    {
        // imwrite("photos/Grayscaleimage.png",originalimage);
        // imwrite("photos/Blurimage.png",blurimage);
        // imwrite("photos/sobelfilter.png",image);
        // imwrite("photos/treshold_200.png",imagethreshold1);
        // imwrite("photos/treshold_150.png",imagethreshold2);
        // imwrite("photos/treshold_100.png",imagethreshold3);
        break;
    }
}
destroyAllWindows();
return 0;
}