#include"../include/imagethreshold.h"

 ImageThreshold::ImageThreshold()
{

}

Mat ImageThreshold::convolution_image(Mat image,Mat filter_)
{
    // this function is used for convolving image with the provided filter
    int x=image.cols;
    int y=image.rows;
    int filter_x=filter_.cols;
    int filter_y=filter_.rows;
    float sum=0;
    // padding is added to the image so that input image and output image became of same size
    int bordersize=(filter_x-1)/2;
    copyMakeBorder(image,image, bordersize,bordersize,bordersize,bordersize,BORDER_REPLICATE,Scalar(0));
    Mat finalimage=Mat::zeros(Size(x,y),CV_32F);
    for (int i=0;i<(finalimage.rows);i++)
    {
        for(int j=0;j<(finalimage.cols);j++)
        {
            for (int a=0;a<(filter_y);a++)
            {
                for(int b=0;b<(filter_x);b++)
                {
                sum+=filter_.at<float>(a,b)*image.at<uchar>(i+a,j+b);
                }
            }
            finalimage.at<float>(i,j)=abs(sum);
            sum=0;
        }
    }
    return finalimage;
}

Mat ImageThreshold::Gaussian_blur(Mat image,int ksize,float std)
{ 
    /**
     * This function is responsible for applying gaussian blur to an image
     */
    float pi=2*acos(0);
    Mat Gfilter=Mat::zeros(Size(ksize,ksize),CV_32F);
    int middlepoint=(int)ksize/2;
    Mat finalimage=Mat::zeros(Size((image.cols),(image.rows)),CV_8U);
    float sum=0;
    for (int i=0;i<ksize;i++)
    {
        for(int j=0;j<ksize;j++)
        {
            float exppower=-(pow((j-middlepoint),2)+pow((i-middlepoint),2))/(2*pow(std,2));
            Gfilter.at<float>(i,j) = (1/(2*pi*pow(std,2)))*exp(exppower);
            sum+=(1/(2*pi*pow(std,2)))*exp(exppower);
        }
    }
    // Gaussian filter is to be normalize so that sum of each components inside the filter must add to 1
    Gfilter=Gfilter/sum;
    Mat Gaussianimage=convolution_image(image,Gfilter);
    normalize(Gaussianimage,Gaussianimage,0,255,NORM_MINMAX);
    // ouput image depth may exceeds 8 bit so its needs to be converted to 8 bit 
    Gaussianimage.convertTo(finalimage,CV_8U);
    return finalimage;
}

Mat ImageThreshold::sobelfilter(Mat image,int x,int y)
{
    // This is filter used for detecting vertical edge
    Mat vlinedetection=(Mat_<float>(3,3) << -1, 0,1, -2, 0,2,-1,0,1);
    // This filter is used for detecting horizontal edge
    Mat hlinedetection=(Mat_<float>(3,3) << -1, -2,-1, 0, 0,0,1,2,1);
    Mat finaloutput=Mat::zeros(Size(image.cols,image.rows),CV_32F);
    // filter is convolve with the images to given vertical and horizontal edge output
    if(x>=1)
    {
            Mat outputafterhfilter=convolution_image(image,vlinedetection);
            finaloutput=finaloutput + outputafterhfilter.mul(outputafterhfilter);
    }
    if(y>=1)
    {
            Mat outputaftervfilter=convolution_image(image,hlinedetection);
             finaloutput=finaloutput+outputaftervfilter.mul(outputaftervfilter);
    }
    sqrt(finaloutput,finaloutput);
    // output may exceed value of 255 and 0 so ouput must be normalize so that max and min value lie between 0 to 255
    normalize(finaloutput,finaloutput,0,255,NORM_MINMAX);
    Mat finalimage=Mat::zeros(Size(image.cols,image.rows),CV_8U);
    finaloutput.convertTo(finalimage,CV_8U);
    return finalimage;
}
Mat ImageThreshold::thresholding(Mat image,int threshold)
{
    /**
     * This fucntion apply thresholding .
     * If pixel value exceed the given threshold value then it is assign to max value possible i.e 255
     * Else it is set to zero
    */
    Mat finalimage=Mat::zeros(Size((image.cols),(image.rows)),CV_8U);
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            if(image.at<uchar>(i,j)>=threshold)
            {
                finalimage.at<uchar>(i,j)=255;
            }
        }
    }
    return finalimage;
}