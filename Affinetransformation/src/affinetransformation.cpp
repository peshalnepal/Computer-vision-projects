#include"../include/affinetransformation.h"
AffineTransformation::AffineTransformation()
{

}
int* AffineTransformation::multiplication(Mat matrix_1,Mat matrix_2)
{    
    
    static int coordinates[3];
     int x_=matrix_1.cols;
     int y_=matrix_1.rows;
     int k =0;
     for(int i=0;i<y_;i++)
     {
      coordinates[k]=0;
      for(int j=0;j<x_;j++)
      {
         coordinates[k]+=int(matrix_1.at<float>(i,j)*matrix_2.at<int>(j,0));
      }
      k++;
     }
     
     return coordinates;
}
Mat AffineTransformation::applytranslation(Mat image,int x_,int y_)
{
    int x=image.cols;
    int y= image.rows;
    Mat mulmatrix= (Mat_<float>(3,3) << 1, 0, x_, 0, 1, y_, 0,0,1);
    Mat imageclone=Mat::zeros(Size(x+x_,y+y_),image.type());
    int* coordinates;
    for(int i=0;i<y;i++)
    {
        for (int j=0;j<x;j++)
        {
         coordinates= multiplication(mulmatrix,(Mat_<int>(3,1) << j,i,1));
         
        if(*(coordinates)>=0&&*(coordinates)<imageclone.cols&&*(coordinates+1)>=0&&*(coordinates+1)<imageclone.rows)
            {
             
             imageclone.at<Vec3b>(*(coordinates+1),*(coordinates))=image.at<Vec3b>(i,j);
            }   
        }
       
    }
    return imageclone;
}
int* AffineTransformation::finalwidthheight(int x_,int y_,float angle)
{
    static int value[2];
    float pi=2*acos(0);
    float radianangle=pi*angle/180;
    int originx=int(x_/2);
    int originy=int(y_/2);
    int centrevaluex,centrevaluey;
    centrevaluex = int(cos(radianangle) * (0 - originx) - sin(radianangle) * (0 - originy));
    centrevaluex = int(((cos(radianangle) * (x_ - originx) - sin(radianangle) * (0 - originy)) >= centrevaluex) ? (cos(radianangle) * (x_ - originx) - sin(radianangle) * (0 - originy)) : centrevaluex);
    centrevaluex = int(((cos(radianangle) * (x_ - originx) - sin(radianangle) * (y_ - originy)) >= centrevaluex) ? (cos(radianangle) * (x_ - originx) - sin(radianangle) * (y_ - originy)) : centrevaluex);
    centrevaluex = int(((cos(radianangle) * (0 - originx) - sin(radianangle) * (y_ - originy)) >= centrevaluex) ? (cos(radianangle) * (0 - originx) - sin(radianangle) * (y_ - originy)) : centrevaluex);
    value[0] = centrevaluex * 2 + 1;
    centrevaluey = int(sin(radianangle) * (0 - originx) + cos(radianangle) * (0 - originy));
    centrevaluey = int(((sin(radianangle) * (x_ - originx) + cos(radianangle) * (0 - originy)) >= centrevaluey) ? (sin(radianangle) * (x_ - originx) + cos(radianangle) * (0 - originy)) : centrevaluey);
    centrevaluey = int(((sin(radianangle) * (x_ - originx) + cos(radianangle) * (y_- originy)) >= centrevaluey) ? (sin(radianangle) * (x_ - originx) + cos(radianangle) * (y_ - originy)) : centrevaluey);
    centrevaluey = int(((sin(radianangle) * (0 - originx) + cos(radianangle) * (y_ - originy)) >= centrevaluey) ? (sin(radianangle) * (0 - originx) + cos(radianangle) * (y_ - originy)) : centrevaluey);
    value[1] = centrevaluey * 2 + 1;
    return value;
}
Mat AffineTransformation::applyrotation(Mat image,float angle)
{
    int x=image.cols;
    int y= image.rows;
    int originx=int(x/2);
    int originy=int(y/2);
    int* finalcordinates;
    finalcordinates=finalwidthheight(x,y,angle);
    Mat imageclone=Mat::zeros(Size(*(finalcordinates),*(finalcordinates+1)),image.type());
    float pi=2*acos(0);
    float radiangle=pi*angle/180;
    Mat mulmatrix= (Mat_<float>(3,3) << cos(radiangle), -sin(radiangle), 0, sin(radiangle), cos(radiangle), 0, 0,0,1);
    cout<<mulmatrix<<endl;
    int* coordinates;
    for(int i=0;i<y;i++)
    {
        for (int j=0;j<x;j++)
        {
         coordinates= multiplication(mulmatrix,(Mat_<int>(3,1) << (j-originx),(i-originy),1));
         *(coordinates)=*(coordinates)+(*(finalcordinates)-1)/2;
         *(coordinates+1)=*(coordinates+1)+(*(finalcordinates+1)-1)/2;  
        if(*(coordinates)>=0&&*(coordinates)<*(finalcordinates)&&*(coordinates+1)>=0&&*(coordinates+1)<*(finalcordinates+1)) 
            {
             imageclone.at<Vec3b>(*(coordinates+1),*(coordinates))=image.at<Vec3b>(i,j);
            }   
        }
    }
    return imageclone;
}
Mat AffineTransformation::applyshear(Mat image,float x_,float y_)
{
    int x=image.cols;
    int y= image.rows;
    Mat mulmatrix= (Mat_<float>(3,3) << 1, x_, 0, y_, 1, 0, 0,0,1);
    Mat imageclone=Mat::zeros(Size(x+abs(int(y*x_)),y+abs(int(x*y_))),image.type());
    int* coordinates;
    for(int i=0;i<y;i++)
    {
        for (int j=0;j<x;j++)
        {
         coordinates= multiplication(mulmatrix,(Mat_<int>(3,1) << j,i,1));
         if(x_<0)
         {
            *(coordinates)=*(coordinates)+abs(int(y*x_));
         }
         if(y_<0)
         {
             *(coordinates+1)=*(coordinates+1)+abs(int(x*y_));
         }
        if(*(coordinates)>=0&&*(coordinates)<imageclone.cols&&*(coordinates+1)>=0&&*(coordinates+1)<imageclone.rows) 
            {
             imageclone.at<Vec3b>(*(coordinates+1),*(coordinates))=image.at<Vec3b>(i,j);
            }   
        }
       
    }
    return imageclone;
}