#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
    string path;
   Mat img;
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
        img=imread(path,IMREAD_GRAYSCALE);
        if(img.empty())
           {
               throw("image not found in the path");
           }
       }
       catch(const char* msg)
       {
          cerr << msg << '\n';
          return 0;
       }
    Mat image1(Size(20,20),CV_16S);
    Mat image2(Size(20,20),CV_16S);
    Mat imagefinal,imageconvert1,imageconvert2;
    GaussianBlur(img,img,Size(5,5),5);
    int scale=1;
    int delta=0;
    Sobel(img,image1,CV_16S,1,0,5,scale,delta,BORDER_CONSTANT);
    Sobel(img,image2,CV_16S,0,1,5,scale,delta,BORDER_CONSTANT);

    convertScaleAbs(image1, imageconvert1);
    convertScaleAbs(image2, imageconvert2);
    addWeighted(imageconvert1,0.5,imageconvert2,0.5,0,imagefinal);
    while(true)
    {
        namedWindow("edge detected",0);
        resizeWindow("edge detected",Size(20,20));
        imshow("edge detected",imagefinal);
        namedWindow("original image",0);
        resizeWindow("original image",Size(20,20));
        imshow("original image",img);
        int key=waitKey(0);
        if(key==27)
        {
        imwrite("photos/edge_detect.png",imagefinal);
        destroyAllWindows();
        break;
        }
    }
    return 0;

}
