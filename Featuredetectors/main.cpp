#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <cmath>
#include "include/featuredetect.h"
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    string path;
    string path1;
    string path2;
    Mat input; //Load as grayscale
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
        input = imread(path, 0);
        input2 = imread(path2, 0);
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
    vector<KeyPoint> keypoints, keypoints2;
    Mat descriptor, descriptor2;
    vector<Mat> Group_of_images;
    vector<Mat> Group_of_images1;

    /*** preexisiting ***/
    cv::Ptr<Feature2D> detector = SIFT::create();
    // detector->detectAndCompute(input, noArray(), keypoints, descriptor);
    // detector->detectAndCompute(input2, noArray(), keypoints2, descriptor2);
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector<DMatch> matches;

    /** By implementing SIFT algorithm **/
    FeatrueDetect ff;
    tie(keypoints, descriptor) = ff.featuresdetect(input);
    tie(keypoints2, descriptor2) = ff.featuresdetect(input2);

    cout << descriptor.size() << endl;
    cout << descriptor2.size() << endl;

    /*
     * For Drawing Descriptor
     */
    matcher->match(descriptor, descriptor2, matches);
    Mat img_matches;
    drawMatches(input, keypoints, input2, keypoints2, matches, img_matches);

    /*
     * For Drawing Keypoints only
     */

    // drawKeypoints(input, keypoints, output, Scalar_<double>::all(-1), DrawMatchesFlags::DEFAULT);
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

        namedWindow("window ", WINDOW_NORMAL);
        imshow("window ", img_matches);

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
            // imwrite("photos/output_descriptor.png", img_matches);
            // imwrite("photos/output_orientation.png", output);
            // imwrite("photos/output_orientation1.png", output2);
            break;
        }
    }
    destroyAllWindows();
    return 0;
}