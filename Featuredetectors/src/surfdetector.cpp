#include "../include/surfdetector.h"
/*
* This function is responsible for calculating Integral image 
*/
Mat SurfDetector::IntegralImages(Mat image)
{
    Mat finalimage = Mat::zeros(Size(image.cols, image.rows), CV_32F);
    Mat images;
    copyMakeBorder(image, images, 1, 1, 1, 1, BORDER_CONSTANT, Scalar(0, 0, 0));
    int image_width = image.cols;
    int image_height = image.rows;
    for (int y = 1; y <= image_height; y++)
    {
        for (int x = 1; x <= image_width; x++)
        {
            float sum = 0;
            images.at<float>(y, x) = images.at<float>(y, x - 1) + images.at<float>(y - 1, x) - images.at<float>(y - 1, x - 1) + images.at<float>(y, x);
            finalimage.at<float>(y - 1, x - 1) = images.at<float>(y, x);
        }
    }
    return finalimage;
}
/*
* This function is Responsible for removing the keypoints that have similar keypoint values and similar angle 
*/
vector<KeyPoint> SurfDetector::removekeypoints(vector<KeyPoint> keypointvect)
{
    vector<KeyPoint> newvectorkeypoint;
    if (keypointvect.size() <= 2)
    {
        return keypointvect;
    }
    for (int j = 0; j < (keypointvect.size() - 1); j++)
    {
        KeyPoint newkeypoint;
        if (keypointvect.at(j).pt != keypointvect.at(j + 1).pt || keypointvect.at(j).angle != keypointvect.at(j + 1).angle)
        {

            newvectorkeypoint.push_back(keypointvect.at(j));
        }
    }
    return newvectorkeypoint;
}
/**
 * This function apply horizontal filter to the image using the box filter of size provided in order to obtain Dxx
*/
Mat SurfDetector:: Horizontalfilterforimage(Mat integratedimage, int size, int scale)
{
    Mat finalimage = Mat::zeros(Size(int(integratedimage.cols), int(integratedimage.rows)), CV_32F);
    int BorderSize = int((size - 1) / 2);
    copyMakeBorder(integratedimage, integratedimage, BorderSize, BorderSize, BorderSize, BorderSize, BORDER_REFLECT, Scalar(0));
    int image_width = finalimage.cols;
    int image_height = finalimage.rows;
    int corners = round(size / 4);
    int tobeadded_x = (size - 2 * corners);
    int tobeadded_y = int(size / 3);
    float check = 0;
    for (int y = 0; y < (image_height); y++)
    {
        for (int x = 0; x < (image_width); x++)
        {

            int xx_axis = (x + corners + tobeadded_x - 1);
            int yy_axis = (y + tobeadded_y - 1);
            float sum = 0;
            if ((yy_axis) < (image_height - BorderSize) && (xx_axis) < (image_width - BorderSize))
            {
                if ((yy_axis - tobeadded_y) < 0)
                {
                    sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x));
                }
                else
                {
                    sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis - tobeadded_x));
                }

                yy_axis = (yy_axis + tobeadded_y);
                sum += -2 * (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis - tobeadded_x));
                yy_axis = (yy_axis + tobeadded_y);
                sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis - tobeadded_x));
                if ((sum) > check)
                {
                    check = sum;
                }
            }
            finalimage.at<float>(y, x) = sum;
        }
    }
    finalimage /=check;
    return finalimage;
}
/**
 * This function apply vertical filter to the image using the box filter of size provided in order to obtain Dyy
*/
Mat SurfDetector::verticalfilterforimage (Mat integratedimage, int size, int scale)
{
    Mat finalimage = Mat::zeros(Size(int(integratedimage.cols), int(integratedimage.rows)), CV_32F);
    int BorderSize = int((size - 1) / 2);
    copyMakeBorder(integratedimage, integratedimage, BorderSize, BorderSize, BorderSize, BorderSize, BORDER_REFLECT, Scalar(0));
    int image_width = finalimage.cols;
    int image_height = finalimage.rows;
    int corners = round(size / 4);
    int tobeadded_y = (size - 2 * corners);
    int tobeadded_x = int(size / 3);
    float check = 0;
    for (int y = 0; y < (image_height); y++)
    {
        for (int x = 0; x < (image_width); x++)
        {

            int yy_axis = (y + corners + tobeadded_y - 1);
            int xx_axis = (x + tobeadded_x - 1);
            float sum = 0;
            if ((yy_axis) < (image_height - BorderSize) && (xx_axis) < (image_width - BorderSize))
            {
                if ((xx_axis - tobeadded_x) < 0)
                {
                    sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis));
                }
                else
                {
                    sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis - tobeadded_x));
                }

                xx_axis = (xx_axis + tobeadded_x);
                sum += -2 * (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis - tobeadded_x));
                xx_axis = (xx_axis + tobeadded_x);
                sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded_x) - integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded_y, xx_axis - tobeadded_x));
                if ((sum) > check)
                {
                    check = sum;
                }
            }
            finalimage.at<float>(y, x) = sum;
        }
    }

    finalimage /= check;
    return finalimage;
}
/**
 * This function apply Diagonal filter to the image using the box filter of size provided in order to obtain Dxy
*/
Mat SurfDetector::Daigonalfilterforimage(Mat integratedimage, int size, int scale)
{
    Mat finalimage = Mat::zeros(Size(int(integratedimage.cols), int(integratedimage.rows)), CV_32F);
    int BorderSize = int((size - 1) / 2);
    copyMakeBorder(integratedimage, integratedimage, BorderSize, BorderSize, BorderSize, BorderSize, BORDER_REFLECT, Scalar(0));
    int image_width = finalimage.cols;
    int image_height = finalimage.rows;
    int middlepart;
    int corners_ = int(round((size - ((size / 3) * 2)) / 3));
    int tobeadded = int(size / 3);
    float check = 0;
    middlepart = size - 2 * tobeadded - 2 * corners_;
    for (int y = 0; y < (image_height); y++)
    {
        for (int x = 0; x < (image_width); x++)
        {
            int xx_axis = (x + tobeadded + corners_ - 1);
            int yy_axis = (y + tobeadded + corners_ - 1);
            float sum = 0;
            if ((y + size) < (image_height) && (x + size) < (image_width))
            {

                sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded) - integratedimage.at<float>(yy_axis - tobeadded, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded, xx_axis - tobeadded));
                xx_axis = (xx_axis + tobeadded + middlepart);
                sum += -(integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded) - integratedimage.at<float>(yy_axis - tobeadded, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded, xx_axis - tobeadded));
                xx_axis = (xx_axis - (tobeadded + middlepart));
                yy_axis = (yy_axis + tobeadded + middlepart);
                sum += -(integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded) - integratedimage.at<float>(yy_axis - tobeadded, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded, xx_axis - tobeadded));
                xx_axis = (xx_axis + (tobeadded + middlepart));
                sum += (integratedimage.at<float>(yy_axis, xx_axis) - integratedimage.at<float>(yy_axis, xx_axis - tobeadded) - integratedimage.at<float>(yy_axis - tobeadded, xx_axis) + integratedimage.at<float>(yy_axis - tobeadded, xx_axis - tobeadded));
                if ((sum) > check)
                {
                    check = sum;
                }
            }
            finalimage.at<float>(y, x) = (sum);
        }
    }
    finalimage /= check;
    return finalimage;
}
/**
 * This function Create 3x3x3 matrix by selecting pixels value around the coordinate value that is passed and from array of images
*/
Mat SurfDetector::createMat3Drix(Mat imagearray[3], int x, int y)
{
    int dims[] = {3, 3, 3};
    Mat Mat3D(3, dims, CV_32F, Scalar::all(0));
    float c11, c00, c22, c02, c20, c10, c12, c01, c21;
    for (int i = 0; i < Mat3D.size[2]; i++)
    {
        for (int k = 0; k < Mat3D.size[1]; k++)
        {
            for (int j = 0; j < Mat3D.size[0]; j++)
            {
                if (x > 1 && y > 1)
                {
                    c11 = imagearray[i].at<float>((y + k - 1), (x + j - 1));
                    c00 = imagearray[i].at<float>((y + k - 1) - 1, (x + j - 1) - 1);
                    c22 = imagearray[i].at<float>((y + k - 1) + 1, (x + j - 1) + 1);
                    c02 = imagearray[i].at<float>((y + k - 1) - 1, (x + j - 1) + 1);
                    c20 = imagearray[i].at<float>((y + k - 1) + 1, (x + j - 1) - 1);
                    c10 = imagearray[i].at<float>((y + k - 1), (x + j - 1) - 1);
                    c12 = imagearray[i].at<float>((y + k - 1), (x + j - 1) + 1);
                    c01 = imagearray[i].at<float>((y + k - 1) - 1, (x + j - 1));
                    c21 = imagearray[i].at<float>((y + k - 1) + 1, (x + j - 1));
                    Mat3D.at<float>(i, k, j) = (0.5*c11 + 0.05 * (c10 + c12 + c01 + c21) + 0.05* (c00 + c22 + c02 + c20));
                }

            }
        }
    }
    return Mat3D;
}
/**
 * This function pass integral image to the three function so that the output of each of those function gives 
 * Gaussian partial derivative in x,y and xy.
 * Using Matrix output from these function hessian determinant is calculated
*/
vector<vector<Mat>> SurfDetector::createfilteredimage(Mat integratedimage, int scale, int octave)
{
    int filtersize = 9;
    vector<vector<Mat>> finalimage;
    vector<vector<Mat>> Requiredimages;

    vector<Mat> Group_of_images;
    vector<Mat> images_required;
    for (int i = 0; i < octave; i++)
    {
        filtersize = 9 + 6 * i;
        for (int j = 0; j < scale; j++)
        {
            Mat verintegratedimage = verticalfilterforimage(integratedimage, filtersize, (((j + 1) * (i + 1))));
            Mat horintegratedimage = Horizontalfilterforimage(integratedimage, filtersize, (j * (i + 1)) + 1);
            Mat Daigonalimage = 0.9 * Daigonalfilterforimage(integratedimage, filtersize, (j * (i + 1)) + 1);
            Mat finalimage = verintegratedimage.mul(horintegratedimage) - Daigonalimage.mul(Daigonalimage);
            Group_of_images.push_back(finalimage);
            filtersize = filtersize + (6 * pow(2, i));
        }
        finalimage.push_back(Group_of_images);
        Group_of_images.clear();
    }

    return finalimage;
}
/**
 * horizontal as well as vertical wavelet response is applied to the image passed to this function
*/
tuple<Mat, Mat> SurfDetector::calculatehaarwavelets(Mat image, int nooftimes, int size)
{
    int filtersize = 4 * size;

    Mat DerX = Mat::zeros(Size(image.cols - filtersize - 1, image.rows - filtersize - 1), CV_32F);
    Mat DerY = Mat::zeros(Size(image.cols - filtersize - 1, image.rows - filtersize - 1), CV_32F);
    Mat storeinput;
    Mat storedifference;
    float weight_calculated = -0.5 / pow((2.5 * size), 2);
    float sum_x = 0;
    float sum_y = 0;
    for (int i = 0; i < DerX.rows; i++)
    {
        for (int j = 0; j < DerX.cols; j++)
        {
            int xx_axis = j;
            int yy_axis = i;
            int x = xx_axis - int(DerX.cols / 2);
            int y = yy_axis - int(DerY.cols / 2);
            DerX.at<float>(i, j) = -image.at<float>(yy_axis, xx_axis) + 2 * image.at<float>(yy_axis, (xx_axis + (filtersize / 2))) - image.at<float>(yy_axis, xx_axis + filtersize) + image.at<float>(yy_axis + filtersize, xx_axis) - 2 * image.at<float>(yy_axis + filtersize, xx_axis + (filtersize / 2)) + image.at<float>(yy_axis + filtersize, xx_axis + filtersize);
            DerX.at<float>(i, j) = DerX.at<float>(i, j) * exp(weight_calculated * (pow(x, 2) + pow(y, 2)));
            sum_x += DerX.at<float>(i, j);
            DerY.at<float>(i, j) = -image.at<float>(yy_axis, xx_axis) + 2 * image.at<float>(yy_axis + (filtersize / 2), xx_axis) - image.at<float>(yy_axis + filtersize, xx_axis) + image.at<float>(yy_axis, xx_axis + filtersize) - 2 * image.at<float>(yy_axis + (filtersize / 2), xx_axis + (filtersize)) + image.at<float>(yy_axis + filtersize, xx_axis + filtersize);
            DerY.at<float>(i, j) = DerY.at<float>(i, j) * exp(weight_calculated * (pow(x, 2) + pow(y, 2)));
            sum_y += DerY.at<float>(i, j);
        }
    }
    return make_tuple(DerX / sum_x, DerY / sum_y);
}
/**
 * calculate vertical and horizontal wavelet response for the descriptor
*/
float *SurfDetector::calculatewaveletsdescriptor(Mat image, int size, int x, int y)
{
    char imgnumber[1] = {'a'};
    char name_[100];
    imgnumber[0] = imgnumber[0] + size;
    int filtersize = 2 * size;
    static float finalsum[4];
    Mat DerX = Mat::zeros(Size(image.cols - filtersize - 1, image.rows - filtersize - 1), CV_32F);
    Mat DerY = Mat::zeros(Size(image.cols - filtersize - 1, image.rows - filtersize - 1), CV_32F);
    Mat storeinput;
    Mat storedifference;
    float weight_calculated = -0.5 / pow((3.3 * size), 2);
    float sum_x = 0;
    float sum_y = 0;
    for (int i = 0; i < DerX.rows; i++)
    {
        for (int j = 0; j < DerX.cols; j++)
        {
            int xx_axis = j;
            int yy_axis = i;
            x = xx_axis - int(DerX.cols / 2);
            y = yy_axis - int(DerY.rows / 2);
            DerX.at<float>(i, j) = -image.at<float>(yy_axis, xx_axis) + 2 * image.at<float>(yy_axis, (xx_axis + (filtersize / 2))) - image.at<float>(yy_axis, xx_axis + filtersize) + image.at<float>(yy_axis + filtersize, xx_axis) - 2 * image.at<float>(yy_axis + filtersize, xx_axis + (filtersize / 2)) + image.at<float>(yy_axis + filtersize, xx_axis + filtersize);
            DerX.at<float>(i, j) = DerX.at<float>(i, j) * exp(weight_calculated * (pow(x, 2) + pow(y, 2)));
            finalsum[0] += DerX.at<float>(i, j);
            finalsum[2] += abs(DerX.at<float>(i, j));
            DerY.at<float>(i, j) = -image.at<float>(yy_axis, xx_axis) + 2 * image.at<float>(yy_axis + (filtersize / 2), xx_axis) - image.at<float>(yy_axis + filtersize, xx_axis) + image.at<float>(yy_axis, xx_axis + filtersize) - 2 * image.at<float>(yy_axis + (filtersize / 2), xx_axis + (filtersize)) + image.at<float>(yy_axis + filtersize, xx_axis + filtersize);
            DerY.at<float>(i, j) = DerY.at<float>(i, j) * exp(weight_calculated * (pow(x, 2) + pow(y, 2)));
            finalsum[1] += DerY.at<float>(i, j);
            finalsum[3] += abs(DerY.at<float>(i, j));
        }
    }
    finalsum[0] /= (DerX.cols * DerX.rows);
    finalsum[1] /= (DerX.cols * DerX.rows);
    finalsum[2] /= (DerX.cols * DerX.rows);
    finalsum[3] /= (DerX.cols * DerX.rows);
    return finalsum;
}
/**
 * This function takes images and keypoints of the image and calculate oreintation for each keypoints using Haar Wavelets
 * Window of size 6s is used to calculate the orientation
*/
vector<KeyPoint> SurfDetector::calculateorientation(Mat image, vector<KeyPoint> keypoints)
{

    int BorderSize = 6 * 20;
    char imgnumber[1] = {'a'};
    char name_[100];
    float pi = 2 * acos(0);
    copyMakeBorder(image, image, BorderSize, BorderSize, BorderSize, BorderSize, BORDER_REPLICATE, Scalar(0));
    for (int i = 0; i < keypoints.size(); i++)
    {
        KeyPoint keypoint = keypoints.at(i);
        float size = keypoint.size / 5;
        size = round(size / 2) * 2;
        int window_size = (6 * size) + 1;
        Mat image_(image, Rect((keypoint.pt.x + BorderSize - window_size), (keypoint.pt.y + BorderSize - window_size), (2 * window_size), (2 * window_size)));
        Mat horwavelet, verwavelet;
        tie(horwavelet, verwavelet) = calculatehaarwavelets(image_, 1, size);
        float sum[6] = {0, 0, 0, 0, 0, 0};
        int checkangle = 0;
        for (int y = 0; y < (horwavelet.rows); y++)
        {
            for (int x = 0; x < (horwavelet.cols); x++)
            {
                int a = y - (horwavelet.rows / 2);
                int b = x - (horwavelet.cols / 2);

                int angle = (atan2(a, b) * 180 / pi);

                while (abs(angle) > 360)
                {
                    angle %= 360;
                }
                if (angle < 0)
                {
                    angle = 360 + angle;
                }

                int value = int(round(angle / 60));
                if (value == 6)
                {
                    value = 0;
                }
                sum[value] += (horwavelet.at<float>(y, x) + verwavelet.at<float>(y, x));
            }
        }
        float value = 0;
        for (int index = 0; index < 6; index++)
        {
            if (value < sum[index])
            {
                value = sum[index];
                keypoints.at(i).angle = 360 - index * 60;
            }
        }
    }
    return keypoints;
}
/**
 * Inital image which is noramlized is passed in this along with keypoints
 * Window of size 20s is taken around the keypoint in the orientation of keypoint 
 * using that window descritor is calculated for the image
*/
Mat SurfDetector::descriptors(Mat initial_image, vector<KeyPoint> keypoints)
{
    int BorderSize = 20 * 20;
    float pi = 2 * acos(0);
    Mat image;
    initial_image.convertTo(image, CV_32F);
    image /= 255;
    copyMakeBorder(image, image, BorderSize, BorderSize, BorderSize, BorderSize, BORDER_REPLICATE, Scalar(0));
    Mat finalimage = Mat::zeros(Size(64, keypoints.size()), CV_32F);
    Mat Rotated_imagewindow;
    char imgnumber[1] = {'a'};
    char name_[100];
    Mat sampleimage;
    for (int i = 0; i < keypoints.size(); i++)
    {
        KeyPoint keypoint = keypoints.at(i);
        int xx_axis = keypoint.pt.x + BorderSize;
        int yy_axis = keypoint.pt.y + BorderSize;
        float angle = 360 - keypoint.angle;
        float size = keypoint.size / 5;
        size = round(size / 2) * 2;
        int window_size = 20 * size + 2;
        Rotated_imagewindow = Mat::zeros(Size(window_size, window_size), CV_32F);
        float weight = 1;
        float subwindowsize = 20 * size / 4;
        int sample_x = 0, sample_y = 0;
        for (int b = 0; b < window_size; b++)
        {
            for (int a = 0; a < window_size; a++)
            {
                int x = a - (Rotated_imagewindow.cols / 2);
                int y = b - (Rotated_imagewindow.rows / 2);
                float Rotatedx_value = x * cos(angle * pi / 180) + y * sin(angle * pi / 180) + xx_axis;
                float Rotatedy_value = -x * sin(angle * pi / 180) + y * cos(angle * pi / 180) + yy_axis;
                if (Rotatedx_value >= 0 && Rotatedx_value < image.cols && Rotatedy_value >= 0 && Rotatedy_value < image.rows)
                {
                    float fractionx = abs((Rotatedx_value - (int)Rotatedx_value));
                    float fractiony = abs((Rotatedy_value - (int)Rotatedy_value));
                    float outputvalue = (weight - fractionx) * (weight - fractiony) * image.at<float>(int(Rotatedy_value), int(Rotatedx_value));
                    outputvalue += (fractionx) * (weight - fractiony) * image.at<float>(int(Rotatedy_value), int(Rotatedx_value) + 1);
                    outputvalue += (weight - fractionx) * (fractiony)*image.at<float>(int(Rotatedy_value) + 1, int(Rotatedx_value));
                    outputvalue += (fractionx) * (fractiony)*image.at<float>(int(Rotatedy_value) + 1, int(Rotatedx_value) + 1);
                    Rotated_imagewindow.at<float>(b, a) = outputvalue;
                }
            }
        }
        Rotated_imagewindow = IntegralImages(Rotated_imagewindow);
        for (int q = 0; q < 4; q++)
        {
            for (int p = 0; p < 4; p++)
            {
                sampleimage = Rotated_imagewindow(Rect(p * subwindowsize, q * subwindowsize, subwindowsize + 2, subwindowsize + 2));
                float *sum;
                sum = calculatewaveletsdescriptor(sampleimage, size, p, q);
                finalimage.at<float>(i, 16 * q + 4 * p) = *sum;
                finalimage.at<float>(i, 16 * q + 4 * p + 1) = *(sum + 1);
                finalimage.at<float>(i, 16 * q + 4 * p + 2) = *(sum + 2);
                finalimage.at<float>(i, 16 * q + 4 * p + 3) = *(sum + 3);
            }
        }
    }
    return finalimage;
}
/**
 * This is function that is called from another class and image is passed to this function
 * output of function that interate the image, apply box filter, calculate orientation of keypoints and 
 * create descriptor for each keypoints are called in this function
*/
tuple<vector<KeyPoint>, Mat> SurfDetector::featuresdetect(Mat initial_image)
{
    int octave = 3;
    int scale = 4;
    vector<Mat> Group_of_images;
    vector<KeyPoint> keypoints;
    Mat descriptor;
    Mat convertedimage;
    initial_image.convertTo(convertedimage, CV_32F);
    convertedimage /= 255;
    Mat integratedimage = IntegralImages(convertedimage);
    vector<vector<Mat>> finalimage;
    finalimage = createfilteredimage(integratedimage, scale, octave);
    char imgnumber[1] = {'a'};
    char name_[100];
    for (int i = 0; i < octave; i++)
    {
        Group_of_images = finalimage.at(i);
        int filtersize = 9;
        for (int j = 1; j < scale - 1; j++)
        {
            filtersize = filtersize + (6 * pow(2, i));
            Mat image = Group_of_images.at(j);
            Mat showimage = Mat::zeros(Size(initial_image.cols, initial_image.rows), CV_8U);
            for (int a = 2; a < image.rows - 2; a++)
            {
                for (int b = 2; b < image.cols - 2; b++)
                {
                    int xx_axis = b;
                    int yy_axis = a;
                    if ((image.at<float>(a, b)) >= 0.04)
                    {
                        Mat imgarray[3] = {Group_of_images.at(j - 1), Group_of_images.at(j), Group_of_images.at(j + 1)};
                        Mat Mat3D = createMat3Drix(imgarray, xx_axis, yy_axis);
                        int minInd[3];
                        int maxInd[3];
                        double min, max;
                        minMaxIdx(Mat3D, &min, &max, minInd, maxInd, Mat());
                        if (max == Mat3D.at<float>(1, 1, 1) && max >= 0.04)
                        {
                            int no_of_attempts = 0;
                            bool reached_destination = false;
                            float dx = 0;
                            float dy = 0;
                            float dxx = 0;
                            float dyy = 0;
                            float dss = 0;
                            float dxy = 0;
                            float dxs = 0;
                            float dys = 0;
                            float dsigma = 0;
                            Mat h = Mat::zeros(Size(1, 3), CV_32F);
                            int value = j;
                            do
                            {
                                dx = 0.5 * (Mat3D.at<float>(1, 1, 2) - Mat3D.at<float>(1, 1, 0));
                                dy = 0.5 * (Mat3D.at<float>(1, 2, 1) - Mat3D.at<float>(1, 0, 1));
                                dsigma = 0.5 * (Mat3D.at<float>(2, 1, 1) - Mat3D.at<float>(0, 1, 1));
                                dxx = (Mat3D.at<float>(1, 1, 2) - 2 * Mat3D.at<float>(1, 1, 1) + Mat3D.at<float>(1, 1, 0));
                                dyy = (Mat3D.at<float>(1, 2, 1) - 2 * Mat3D.at<float>(1, 1, 1) + Mat3D.at<float>(1, 0, 1));
                                dss = (Mat3D.at<float>(2, 1, 1) - 2 * Mat3D.at<float>(1, 1, 1) + Mat3D.at<float>(0, 1, 1));
                                dxy = 0.25 * (Mat3D.at<float>(1, 2, 2) - Mat3D.at<float>(1, 2, 0) - Mat3D.at<float>(1, 0, 2) + Mat3D.at<float>(1, 0, 0));
                                dxs = 0.25 * (Mat3D.at<float>(2, 1, 2) - Mat3D.at<float>(2, 1, 0) - Mat3D.at<float>(0, 1, 2) + Mat3D.at<float>(0, 1, 0));
                                dys = 0.25 * (Mat3D.at<float>(2, 2, 1) - Mat3D.at<float>(2, 0, 1) - Mat3D.at<float>(0, 2, 1) + Mat3D.at<float>(0, 0, 1));
                                Mat Dx = (Mat_<float>(3, 1) << dx, dy, dsigma);
                                Mat Hx = (Mat_<float>(3, 3) << dxx, dxy, dxs, dxy, dyy, dys, dxs, dys, dss);
                                h = -((Hx).inv()) * Dx;
                                if (abs(h.at<float>(0, 0)) >= 0.5)
                                {
                                    xx_axis = xx_axis + (int)round(h.at<float>(0, 0));
                                }
                                if (abs(h.at<float>(1, 0)) >= 0.5)
                                {
                                    yy_axis = yy_axis + (int)round(h.at<float>(1, 0));
                                }
                                if (abs(h.at<float>(2, 0)) >= 0.5)
                                {
                                    value = value + (int)round(h.at<float>(2, 0));
                                }
                                if (abs(h.at<float>(0, 0)) < 0.5 && abs(h.at<float>(1, 0)) < 0.5 && abs(h.at<float>(2, 0)) < 0.5)
                                {
                                    reached_destination = true;
                                    break;
                                }
                                if (xx_axis < 0 || xx_axis >= Group_of_images.at(j).cols || yy_axis < 0 || yy_axis >= Group_of_images.at(j).rows || value < 0 || value >= Group_of_images.size())
                                {
                                    reached_destination = false;
                                }
                                else
                                {
                                    reached_destination = true;
                                }
                                no_of_attempts++;
                            } while (no_of_attempts < 5);

                            if (reached_destination == true)
                            {
                                Mat Dx = (Mat_<float>(3, 1) << dx, dy, dsigma);
                                Mat trans_Dx;
                                transpose(Dx, trans_Dx);
                                float D_;
                                D_ = Mat3D.at<float>(1, 1, 1) + 0.5 * Dx.dot(h);
                                if (abs(D_) >= 0.04)
                                {
                                    float alpha = pow((dxx + dyy), 2);
                                    float beta = (dxx * dyy) - dxy * dxy;
                                    float eigenratio = 10;
                                    if (beta > 0 && (alpha * eigenratio) < (beta * pow((eigenratio + 1), 2)))
                                    {
                                        showimage.at<uchar>(a, b) = 255;
                                        KeyPoint keypoint;
                                        keypoint.pt = Point(xx_axis, yy_axis);
                                        keypoint.octave = octave + value * pow(2, 8) + int(round(((maxInd[2] - 1) + 0.5) * 255)) * pow(2, 16);
                                        keypoint.size = (filtersize + value * (6 * pow(2, i))) * (1.2 / 9) * 5;
                                        keypoint.response = abs(Mat3D.at<float>(1, 1, 1));
                                        keypoint.angle = 0;
                                        keypoints.push_back(keypoint);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    sort(keypoints.begin(), keypoints.end(), sortkeypoint);
    vector<KeyPoint> newkeypoints;
    newkeypoints = calculateorientation(integratedimage, keypoints);
    newkeypoints = removekeypoints(newkeypoints);
    descriptor = descriptors(initial_image, newkeypoints);
    return make_tuple(newkeypoints, descriptor);
}