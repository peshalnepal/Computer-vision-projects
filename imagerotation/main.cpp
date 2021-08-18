#include<iostream>
#include<opencv2/highgui.hpp>

#include<opencv2/imgcodecs.hpp>

#include<opencv2/imgproc.hpp>

#include<math.h>

#include<string>

#include"ImageRotation.h"
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    string path;
    cout << path << endl;
    Mat image = imread(path, IMREAD_COLOR);
    int angle = 45;
    string clockanticlock;
    bool clockwise = false;
    try
    {
        if (argc >= 2)
        {
            angle = stoi(argv[1]);
        }
        if (argc >= 3)
        {
            clockanticlock = argv[2];
            if (clockanticlock == "T" || clockanticlock == "t")
            {
                clockwise = true;
            }
            else if (clockanticlock == "f" || clockanticlock == "F")
            {
                clockwise = false;
            }
            else
            {
                throw ("Enter \"t\" for true and \"f\" for false");
            }
        }
        path = "photos/check.png";
        if (argc >= 4)
        {
            path = argv[3];
        }
        image = imread(path, IMREAD_COLOR);
        if (image.empty())
        {
            throw ("image not found in the path");
        }
    }
    catch (const char *msg)
    {
        cerr << msg << '\n';
        return 0;
    }
    Mat img;
    ImageRotation imagerotate;
    img = imagerotate.imagerotationalgorithm(image, angle, clockwise);
    while (true)
    {
        namedWindow("peshal", WINDOW_NORMAL);
        resizeWindow("peshal", Size(500, 500));
        imshow("peshal", img);
        int k = waitKey(0);
        if (k == 27)
        {
            imwrite("photos/anticlockwise.png",img);
            break;
        }
    }
    destroyAllWindows();
    return 0;
}
