#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
#include "include/featuredetect.h"
#include "include/surfdetector.h"
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
            path = "photos/picture.png";
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
    vector<KeyPoint> keypoints, keypoints2,keypoints_Surf, keypoints2_Surf;
    Mat descriptor, descriptor2, descriptor_Surf, descriptor2_Surf;
    vector<Mat> Group_of_images;
    vector<Mat> Group_of_images1;

    /*** preexisiting ***/
    // cv::Ptr<Feature2D> Siftdetector = SIFT::create();
    // Ptr<SURF> Surfdetector = SURF::create( minHessian );
    // Siftdetector->detectAndCompute(input, noArray(), keypoints, descriptor);
    // Siftdetector->detectAndCompute(input2, noArray(), keypoints2, descriptor2);
    // Surfdetector->detect(input,keypoints2,noArray());

    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector<DMatch> matches_SIFT,matches_SURF;

    /** By implementing SIFT algorithm **/
    FeatrueDetect ff_sift;
    tie(keypoints, descriptor) = ff_sift.featuresdetect(input);
    tie(keypoints2, descriptor2) = ff_sift.featuresdetect(input2);

    /** By implementing SURF algorithm **/
    SurfDetector ff_Surf;
    tie(keypoints_Surf, descriptor_Surf) = ff_Surf.featuresdetect(input);
    tie(keypoints2_Surf, descriptor2_Surf) = ff_Surf.featuresdetect(input2);

    /*
     * For Drawing Descriptor
     */
    matcher->match(descriptor, descriptor2, matches_SIFT);
    Mat img_matches_Sift;
    drawMatches(input, keypoints, input2, keypoints2, matches_SIFT, img_matches_Sift);

    matcher->match(descriptor_Surf, descriptor2_Surf, matches_SURF);
    Mat img_matches_Surf;
    drawMatches(input, keypoints_Surf, input2, keypoints2_Surf, matches_SURF, img_matches_Surf);
    /*
     * For Drawing Keypoints only
     */

    // drawKeypoints(input, keypoints, output, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);

    // drawKeypoints(input2, keypoints2, output2, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);
    // drawKeypoints(input2, keypoints2, output2, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);

    /*
     * For Drawing Keypoints and orientation
     */
    // drawKeypoints(input,keypoints,output,Scalar_<double>::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    // drawKeypoints(input2,keypoints2,output2,Scalar_<double>::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    while (true)
    {

        /*
        * For showing Descriptor
        */

        namedWindow("window SIFT", WINDOW_NORMAL);
        imshow("window SIFT", img_matches_Sift);
        namedWindow("window SURF", WINDOW_NORMAL);
        imshow("window SURF", img_matches_Surf);
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
            // imwrite("photos/output_descriptor_surf.png", img_matches_Surf);
            // imwrite("photos/output_orientation.png", output);
            // imwrite("photos/output_orientation1.png", output2);
            break;
        }
    }
    destroyAllWindows();
    return 0;
}