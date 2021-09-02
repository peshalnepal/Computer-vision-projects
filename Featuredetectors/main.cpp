#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
#include "include/featuredetect.h"
using namespace std;
using namespace cv;
int main()
{
    string path = "photos/picture.png";
    string path1 = "photos/picture1.png";
    string path2 = "photos/picture1.png";
    const Mat input = imread(path, 0); //Load as grayscale
    const Mat input1 = imread(path1, 0);
    const Mat input2 = imread(path2, 0);
    vector<Mat> finalimage;
    Mat output;
    Mat output1;
    Mat output2;
    vector<KeyPoint> keypoints, keypoints1, keypoints2;
    
    vector<Mat> Group_of_images;
    vector<Mat> Group_of_images1;

    /*** preexisiting ***/
    cv::Ptr<Feature2D> detector = SIFT::create();
    detector->detect(input, keypoints);
    detector->detect(input1, keypoints1);
    /** By implementing SIFT algorithm **/
     FeatrueDetect ff;
    keypoints2=ff.featuresdetect(input2);
    drawKeypoints(input, keypoints, output);
    drawKeypoints(input1, keypoints1, output1);
    drawKeypoints(input2, keypoints2, output2);
    char imgnumber[1] = {'a'};
    char name_[100];
    while (true)
    {
        imshow("window", output);
        imshow("window 1", output1);
        imshow("window 2", output2);
        int k = waitKey(0);
        if (k == 27)
        {
            imwrite("photos/output_from_existingfunction.png",output1);
            imwrite("photos/output_from_algorithm.png",output2);
            break;
        }
    }
    destroyAllWindows();
    return 0;
}