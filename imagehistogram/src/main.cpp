#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
void printpixelsvalue(Mat histogramm,int hist_Size,string typeofhist);
int main()
{
//Histogram is collected counts of data organized into set of predefined bins
// histSize defines there are 256 bins where pixel with similar value are kept
int histSize = 256;
// It define x-axis w
float range[] = { 0, 256 };
const float *histrange[]={range};
Mat img_COLOR=imread("photos/demo.png",IMREAD_COLOR);
Mat img;
cvtColor(img_COLOR,img,COLOR_BGR2GRAY);
cout<<"Image size = "<<img.size<<endl;
cout<<"Total pixels in the image = "<<img.rows*img.cols<<endl;
//here vector containing matrix is created to store color channels after they were splitted from the actual image
vector<Mat> imgGRAY;
vector<Mat> imRGB;
split(img,imgGRAY);
split(img_COLOR,imRGB);
Mat gray_hist,blue_hist,green_hist,red_hist;
// As imgGRAY image is grayscale image it consists of 1 color channel so we can plot 1 histogram for grayscale channel
calcHist(&imgGRAY[0],1,0,Mat(),gray_hist,1,&histSize,histrange,true,false);
// As img_COLOR image is colored image it consists of 3 color channel so we can plot 3 histogram for each color channel
calcHist(&imRGB[0],1,0,Mat(),blue_hist,1,&histSize,histrange,true,false);
calcHist(&imRGB[1],1,0,Mat(),green_hist,1,&histSize,histrange,true,false);
calcHist(&imRGB[2],1,0,Mat(),red_hist,1,&histSize,histrange,true,false);
//width and height of image in which we are plotting the histogram
int width=512;
int height=428;
//size of bin, efine width of bin
int container=cvRound(width/histSize);
// Maat of given width and height is created of 3 channels and pixel depth of 8bit
// initially 255 is assign to every pixels of created matrix
Mat histgrayimage(height,width,CV_8UC3,Scalar(255,255,255));
Mat histrgbimage(height,width,CV_8UC3,Scalar(255,255,255));
//this fucntion is responsible for printing the max no of pixel in particular pixel value
printpixelsvalue(gray_hist,256,"gray");
printpixelsvalue(blue_hist,256,"blue");
printpixelsvalue(green_hist,256,"green");
printpixelsvalue(red_hist,256,"red");
//normailzing histogram for each channels
normalize(gray_hist, gray_hist, 0, histgrayimage.rows, NORM_MINMAX, -1, Mat() );
normalize(blue_hist, blue_hist, 0, histgrayimage.rows, NORM_MINMAX, -1, Mat() );
normalize(green_hist, green_hist, 0, histgrayimage.rows, NORM_MINMAX, -1, Mat() );
normalize(red_hist, red_hist, 0, histgrayimage.rows, NORM_MINMAX, -1, Mat() );
// creating histogram in the given image
for (int i=1;i<histSize;i++ )
{
line(histgrayimage,Point(container*(i-1),height-cvRound(gray_hist.at<float>(i-1))),Point(container*(i),height-cvRound(gray_hist.at<float>(i))),Scalar(0,0,0),1,LINE_AA);
line(histrgbimage,Point(container*(i-1),height-cvRound(blue_hist.at<float>(i-1))),Point(container*(i),height-cvRound(blue_hist.at<float>(i))),Scalar(255,0,0),1,LINE_AA);
line(histrgbimage,Point(container*(i-1),height-cvRound(green_hist.at<float>(i-1))),Point(container*(i),height-cvRound(green_hist.at<float>(i))),Scalar(0,355,0),1,LINE_AA);
line(histrgbimage,Point(container*(i-1),height-cvRound(red_hist.at<float>(i-1))),Point(container*(i),height-cvRound(red_hist.at<float>(i))),Scalar(0,0,255),1,LINE_AA);
}
while(true)
{
namedWindow("Display gray Window", WINDOW_FREERATIO);
resizeWindow("Display gray Window",Size(500,500));
imshow("Display gray Window",img);
namedWindow("Display color Window", WINDOW_FREERATIO);
resizeWindow("Display color Window",Size(500,500));
imshow("Display color Window",img_COLOR);
imshow("Histogram grayscale",histgrayimage);
imshow("Histogram RGB",histrgbimage);

int k = waitKey(0);
if(k=='s')
{
imwrite("photos/histogram_for_grayscale_image.png",histgrayimage);
imwrite("photos/histogram_for_rgb_image.png",histrgbimage);
imwrite("photos/grayscale_image.png",img);
break;
}
}
destroyAllWindows();
return 0;
}
void printpixelsvalue(Mat histogramm,int hist_Size,string typeofhist)
{
int pixelintensity=0;
float no_of_pixel=0;
float previous_pixel=0;
for (int j=1;j<hist_Size;j++ )
{
    no_of_pixel=histogramm.at<float>(j-1);
    if(no_of_pixel<previous_pixel)
    {
    no_of_pixel=previous_pixel;
    }
    else
    {
    pixelintensity=j;
    }
    previous_pixel=no_of_pixel;
    }
    cout<<no_of_pixel<<" pixels has intensity "<<pixelintensity<<" "<<typeofhist<<" channels of image"<<endl;
}
