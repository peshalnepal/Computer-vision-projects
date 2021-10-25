#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include"affinetransformation.h"
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
          string path;
          Mat image;
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
        image=imread(path,IMREAD_COLOR);
        if(image.empty())
           {
               throw("image not found in the path");
           }
       }
       catch(const char* msg)
       {
          cerr << msg << '\n';
          return 0;
       }

    AffineTransformation affinetransform;
    Mat img=affinetransform.applyrotation(image,100);
    img=affinetransform.applytranslation(img,100,100);
    // Mat img=affinetransform.applyshear(image,-0.1,-0.1);
    while(true)
    {
        namedWindow("image shown",WINDOW_NORMAL);
        resizeWindow("image shown",500,500);
        imshow("image shown",img);
        int k=waitKey(0);
        if(k==27)
        {
            // imwrite("photos/sheared.png",img);
            break;
        }
    }
    destroyAllWindows();
    return 0;
}