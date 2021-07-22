#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
Mat img=imread("../photos/imagebeforeblur.png");
GaussianBlur(img,img,Size(5,5),5);
cout<<img.size<<endl;
while(true)
    {
    imshow("Display window",img);
    int k =waitKey(0);
    if(k=='s')
        {
        imwrite("../photos/imageafterblur.png",img);
        break;
        }
    }
destroyAllWindows();
return 0;
}
