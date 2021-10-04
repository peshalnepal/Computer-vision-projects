#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
#include <time.h>
#include "include/featuredetect.h"
#include "include/surfdetector.h"
#include "include/Orb.h"
using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
int main(int argc, char *argv[])
{
    string path;
    string path1;
    string path2;
    Mat input;
    Mat input2;
    try
    {

        if (argc <= 2)
        {
            path = "photos/picture1.png";
            path2 = "photos/picture2.png";
        }
        if (argc == 3)
        {
            path = argv[1];
            path2 = argv[2];
        }
        input = imread(path, IMREAD_GRAYSCALE);
        input2 = imread(path2, IMREAD_GRAYSCALE);
        if (input.empty() || input2.empty())
        {
            throw("image not found in the path");
        }
    }
    catch (const char *msg)
    {
        cerr << msg << '\n';
        return 0;
    }

    vector<Mat> finalimage;
    Mat output;
    Mat output2;
    vector<KeyPoint> keypoints, keypoints2, keypoints_Surf, keypoints2_Surf,keypoints_ORB, keypoints2_ORB;
    Mat descriptor, descriptor2, descriptor_Surf, descriptor2_Surf,descriptor_ORB, descriptor2_ORB;
    vector<Mat> Group_of_images;
    vector<Mat> Group_of_images1;

    /*** preexisiting ***/
    // int minHessian=400;
    // cv::Ptr<Feature2D> Siftdetector = SIFT::create();
    // Ptr<SURF> Surfdetector = SURF::create( minHessian );
    // Siftdetector->detectAndCompute(input, noArray(), keypoints, descriptor);
    // Siftdetector->detectAndCompute(input2, noArray(), keypoints2, descriptor2);
    // Surfdetector->detect(input,keypoints2,noArray());

    // Ptr<Feature2D> orb = ORB::create(100);
    // orb->detectAndCompute(input, Mat(), keypoints, descriptor);
    // orb->detectAndCompute(input2, Mat(), keypoints2, descriptor2);
    // cout << int(descriptor.at<char>(1, 1)) << endl;
    // cout << int(descriptor2.at<char>(1, 1)) << endl;

    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    Ptr<DescriptorMatcher> ORB_matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
    std::vector<DMatch> matches_SIFT, matches_SURF, matches_orb;

    /**
     * Implementation of ORB feature detector 
    */

    clock_t t1, t2;

    t1 = clock();

    //Your code here

    //Time taken for running your code segment

    Orbfeaturedetector ff_orb(100);
    tie(keypoints_ORB, descriptor_ORB) = ff_orb.featuresdetect(input);
    tie(keypoints2_ORB, descriptor2_ORB) = ff_orb.featuresdetect(input2);
    t2 = clock();
    double time_dif = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "ORB time " << time_dif << endl;

    t1 = clock();
    /** By implementing SIFT algorithm **/
    FeatrueDetect ff_sift;
    tie(keypoints, descriptor) = ff_sift.featuresdetect(input);
    tie(keypoints2, descriptor2) = ff_sift.featuresdetect(input2);

    t2 = clock();
    time_dif = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "SIFT time " << time_dif << endl;

    t1 = clock();
    // /** By implementing SURF algorithm **/
    SurfDetector ff_Surf;
    tie(keypoints_Surf, descriptor_Surf) = ff_Surf.featuresdetect(input);
    tie(keypoints2_Surf, descriptor2_Surf) = ff_Surf.featuresdetect(input2);

    t2 = clock();
    time_dif = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "SURF time " << time_dif << endl;
    // /*
    //  * For Drawing Descriptor
    //  */
    matcher->match(descriptor, descriptor2, matches_SIFT);
    Mat img_matches_Sift;
    drawMatches(input, keypoints, input2, keypoints2, matches_SIFT, img_matches_Sift);

    matcher->match(descriptor_Surf, descriptor2_Surf, matches_SURF);
    Mat img_matches_Surf;
    drawMatches(input, keypoints_Surf, input2, keypoints2_Surf, matches_SURF, img_matches_Surf);

    ORB_matcher->match(descriptor_ORB, descriptor2_ORB, matches_orb);
    Mat img_matches_orb;
    drawMatches(input, keypoints_ORB, input2, keypoints2_ORB, matches_orb, img_matches_orb);
    /*
     * For Drawing Keypoints only
     */

    // drawKeypoints(input, keypoints, output, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);

    // drawKeypoints(input,keypoints,output, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);
    // drawKeypoints(input2, keypoints2, output2, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);

    /*
     * For Drawing Keypoints and orientation
     */
    // drawKeypoints(input,keypoints,output,Scalar_<double>::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // drawKeypoints(input2,keypoints2,output2,Scalar_<double>::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    while (true)
    {
        // imshow("original image", input);

        /*
        * For showing Descriptor
        */

        namedWindow("window SIFT", WINDOW_NORMAL);
        imshow("window SIFT", img_matches_Sift);
        namedWindow("window SURF", WINDOW_NORMAL);
        imshow("window SURF", img_matches_Surf);
        namedWindow("window ORB", WINDOW_NORMAL);
        imshow("window ORB", img_matches_orb);
        /*
        * For showing Keypoints and orientation
        */
        // namedWindow("window ", WINDOW_NORMAL);
        // imshow("window ", output);
        // namedWindow("window 1",WINDOW_NORMAL);
        // imshow("window 1", output2);
        int k = waitKey(0);
        if (k == 27)
        {
            // imwrite("photos/output_descriptor_orb.png", img_matches_orb);
            // imwrite("photos/output_orientation.png", output);
            // imwrite("photos/output_orientation1.png", output2);
            break;
        }
    }
    destroyAllWindows();
    return 0;
}