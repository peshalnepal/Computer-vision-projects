#include<iostream>

#include<opencv2/highgui.hpp>

#include<opencv2/imgcodecs.hpp>

#include<opencv2/imgproc.hpp>

#include<math.h>

#include<fstream>

#include<string>


using namespace std;
using namespace cv;

void Houghtransform(Mat *linedetectedimage, float threshold, int thickness_ = 1) {
    int rows = (*linedetectedimage).rows;
    int columns = (*linedetectedimage).cols;
    Mat outputedge = (*linedetectedimage).clone();
    int p = rows + columns;
    int value;
    double radianvalue;
    Mat check;
    double pi = 2 * acos(0.0);
    check = Mat::zeros(Size(360, p), CV_8U);
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((*linedetectedimage).at<uchar>(i, j) > 127) {
                k = 0;
                while (k < 360) {
                    radianvalue = pi / 180.0 * k;
                    value = int(i * sin(radianvalue) + j * cos(radianvalue));
                    if (value >= 0) {
                        check.at<uchar>(value, k) += 1;
                    }

                    k = k + 3;
                }
            }
        }
    }

    *linedetectedimage = Mat::zeros(Size(columns, rows), CV_8U);
    double minVal;
    double maxVal;
    minMaxLoc(check, &minVal, &maxVal);

    //cout<<"check 1"<<endl;
    k = 0;
    while (k < 360) {
        for (int i = 0; i < p; i++) {
            if (check.at<uchar>(i, k) >= (threshold * maxVal)) {
                int coordinate[2][2];
                radianvalue = pi / 180.0 * k;
                int y1 = 0;
                int y2 = 0;
                int x1 = 0;
                int x2 = 0;
                if (k == 0 || k == 180) {
                    if (i >= 0 && i < columns) {
                        line((*linedetectedimage), Point(i, 0), Point(i, rows - 1), 255, thickness_);
                    }

                } else if (k == 90 || k == 270) {
                    if (i >= 0 && i < rows) {
                        line((*linedetectedimage), Point(0, i), Point(columns - 1, i), 255, thickness_);
                    }
                } else {
                    y1 = int(i / sin(radianvalue));

                    if (y1 < 0) {

                        x1 = int(i / cos(radianvalue));

                        if (x1 >= 0 && x1 < columns) {
                            coordinate[0][0] = x1;
                            coordinate[0][1] = 0;

                        }
                    } else if (y1 >= rows) {
                        x1 = int(i / cos(radianvalue) - ((rows - 1) * sin(radianvalue) / cos(radianvalue)));
                        if (x1 >= 0 && x1 < columns) {
                            coordinate[0][0] = x1;
                            coordinate[0][1] = rows - 1;
                        }
                    } else {
                        coordinate[0][0] = 0;
                        coordinate[0][1] = y1;
                    }
                    y2 = int(i / sin(radianvalue) - ((columns - 1) * cos(radianvalue) / sin(radianvalue)));
                    if (y2 < 0) {
                        x2 = int(i / cos(radianvalue));
                        if (x2 >= 0 && x2 < columns) {
                            coordinate[1][0] = x2;
                            coordinate[1][1] = 0;
                        }
                    } else if (y2 >= rows) {
                        x2 = int(i / cos(radianvalue) - ((rows - 1) * sin(radianvalue) / cos(radianvalue)));
                        if (x2 >= 0 && x2 < columns) {
                            coordinate[1][0] = x2;
                            coordinate[1][1] = rows - 1;
                        }
                    } else {
                        coordinate[1][0] = columns - 1;
                        coordinate[1][1] = y2;
                    }
                    line((*linedetectedimage), Point(coordinate[0][0], coordinate[0][1]),
                         Point(coordinate[1][0], coordinate[1][1]), 255, thickness_);
                }

            }
        }
        k = k + 3;
    }
    //cout<<"check 2"<<endl;
}

float median(Mat channel) {
    float m = (channel.rows * channel.cols) / 2;
    int bin = 0;
    double med = -1.0;
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    Mat hist;
    calcHist(&channel, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, false);

    for (int i = 0; i < histSize && med < 0.0; ++i) {
        bin += cvRound(hist.at<float>(i));
        if (bin > m && med < 0.0)
            med = i;
    }
    return med;
}

int main(int argc, char *argv[]) {
    VideoCapture capvideo;
    ifstream ifile;
    string device;
    try {

        if (argc <= 2) {
            capvideo.open(0);
        }
        if (argc >= 3) {
            device = argv[1];
            if (device == "V" || device == "v") {
                ifile.open(argv[2]);
                if (!ifile) {
                    throw ("video not found in the path");
                }
                capvideo.open(argv[2]);
                if (!capvideo.isOpened()) {
                    throw ("video not found in the path");
                }
            } else if (device == "c" || device == "C") {

                capvideo.open(stoi(argv[2]));
                if (!capvideo.isOpened()) {
                    throw ("Camera not found");
                }
            } else {
                capvideo.open(0);
            }
        }
    }

    catch (const char *msg) {
        cerr << msg << '\n';
        return 0;
    }

    Mat outputedge;
    Mat originalimg;
    Mat img;
    Mat Grayimg;
    double medianvalue = 0;
    float lower, upper;
    int loopoptimize = 0;
    //originalimg=imread("../photos/check.png",IMREAD_COLOR);
    int FPS = capvideo.get(CAP_PROP_FPS);
    int width = capvideo.get(CAP_PROP_FRAME_WIDTH);
    int height = capvideo.get(CAP_PROP_FRAME_HEIGHT);
    //VideoWriter Videowrite("../videos/outputcolor.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), double(FPS),Size(width, height), true);
    while (true) {
        capvideo.read(originalimg);
        cvtColor(originalimg, Grayimg, COLOR_BGR2GRAY);
        if (Grayimg.empty()) {
            return 0;
        }
        GaussianBlur(Grayimg, img, Size(5, 5), 5);
        if (loopoptimize % (FPS) == 0) {
            medianvalue = median(img);
            lower = ((0.7 * medianvalue) > 0) ? (0.7 * medianvalue) : 0;
            upper = ((1.3 * medianvalue) < 255) ? (1.3 * medianvalue) : 255;
        }
        Canny(img, outputedge, lower, upper);
        Houghtransform(&outputedge, 0.9, 2);
        cvtColor(outputedge, outputedge, COLOR_GRAY2BGR);
        addWeighted(outputedge, 0.5, originalimg, 0.5, 0.1, outputedge);
        namedWindow("canny edge", WINDOW_NORMAL);
        resizeWindow("canny edge", 500, 500);
        imshow("canny edge", outputedge);
        //Videowrite.write(outputedge);
        int k = waitKey(5);
        if (k == 27) {
            break;
        }
        loopoptimize++;
    }
    capvideo.release();

    // Videowrite.release();
    destroyAllWindows();

    return 0;
}
