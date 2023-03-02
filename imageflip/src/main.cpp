#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
void flipimage(Mat* img, Mat* dimg,int h_v);
int main(int argc, char* argv[])
{
      Mat image_;
      string path;
       try
       {
        if (argc==1)
            {
                path="photos/image.png";
            }
        if(argc >=2)
            {
                path=argv[1];
            }
        image_=imread(path,IMREAD_COLOR);
        if(image_.empty())
           {
               throw("image not found in the path");
           }
       }
       catch(const char* msg)
       {
          cerr << msg << '\n';
          return 0;
       }
Mat grayscaleimage=image_.clone();
cvtColor(grayscaleimage,grayscaleimage,COLOR_BGR2GRAY);
Mat color_imageh,color_imagev,gray_imagev,gray_imageh;
cout<<image_.size<<endl;
if(image_.empty())
{
cout<<"sorry no image"<<endl;
return 0;
}
// address of image is to be passed so that rather than copy original image is passed with their header and pointer to the matrix
// As a result we can pass any image as source and any image as destination
//0 means horizontal flip and 1 means vetical flip
flipimage(&image_,&color_imageh,0);
flipimage(&image_,&color_imagev,1);
flipimage(&grayscaleimage,&gray_imageh,0);
flipimage(&grayscaleimage,&gray_imagev,1);
while(true)
{
imshow("original image",image_);
imshow("grayscale image",grayscaleimage);
imshow("hotizontal flip image",color_imageh);
imshow("vertical flip image",color_imagev);
imshow("horizontal flip gray image",gray_imageh);
imshow("vertical flip gray image",gray_imagev);
int k =waitKey(0);
if(k==27)
{
destroyAllWindows();
break;
}
}
return 0;
}
void flipimage(Mat* img,Mat* dimg,int h_v)
{
// input image can be of any depth so they needs to changed to 8 bit depth
(*img).convertTo((*img),CV_8U);
//destination image must have similar property as that of original image
*dimg=(*img).clone();
cout<<(*img).channels()<<endl;
// if the image is gray scale image the we expect 8bit or uchar as output from each pixel
// if image is colored image, we expect Vector of 8bit or 1 byte as output from pixel from all three channel
// so we are checking wether image is grayscal or not
if((*img).channels()==1)
{
for(int i=0;i<(*img).rows;i++)
{
    for(int j=0;j<(*img).cols;j++)
    {
    if(h_v==1)
    {
    (*dimg).at<uchar>(i,j)=(*img).at<uchar>(i,((*img).cols-1)-j);
    }
    if(h_v==0)
    {
        (*dimg).at<uchar>(i,j)=(*img).at<uchar>(((*img).rows-1)-i,j);
    }
    }
}
}
else
{
for(int i=0;i<(*img).rows;i++)
{
    for(int j=0;j<(*img).cols;j++)
    {
    if(h_v==1)
    {
    (*dimg).at<Vec3b>(i,j)=(*img).at<Vec3b>(i,((*img).cols-1)-j);
    }
    if(h_v==0)
    {
        (*dimg).at<Vec3b>(i,j)=(*img).at<Vec3b>(((*img).rows-1)-i,j);
    }
    }

}
}

}
