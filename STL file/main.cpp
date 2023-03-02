#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>
#include "include/imagetostl.h"
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    string path, path2, path3;
    vector<Mat> input;
    try
    {
        if (argc < 2)
        {
            path = "photos/check.png";
            path2 = "photos/check2.png";
            path3 = "photos/check3.png";
        }
        if (argc == 2)
        {
            path = argv[1];
        }
        input.push_back(imread(path, IMREAD_COLOR));
        input.push_back(imread(path2, IMREAD_COLOR));
        input.push_back(imread(path3, IMREAD_COLOR));
        if (input.empty())
        {
            throw("image not found in the path");
        }
    }
    catch (const char *msg)
    {
        cerr << msg << '\n';
        return 0;
    }
    ImageToStl imgstl;
    input = imgstl.sortimages(input);
    vector<Mat>::iterator iter;
    string window_name;
    char charconcat[1] = {'a'};

    while (true)
    {
        for (iter = input.begin(); iter != input.end(); iter++)
        {
            window_name= "window display ";
            window_name.append(charconcat);
            imshow(window_name, *(iter));
            charconcat[0] += 1;
        }
        int k = waitKey(0);
        if (k == 27)
        {
            break;
        }
    }
    destroyAllWindows();
    return 0;
}
