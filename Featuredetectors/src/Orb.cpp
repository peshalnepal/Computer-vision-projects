#include "../include/Orb.h"
Orbfeaturedetector::Orbfeaturedetector(int totalkeypoints)
{
    keypointdisplay = totalkeypoints;
}
vector<Mat> Orbfeaturedetector::scalespace(Mat image, int scalingfactor)
{
    vector<Mat> scaledimage;
    image.convertTo(image, CV_32F);
    image /= 255;
    for (int i = 0; i < scalingfactor; i++)
    {
        scaledimage.push_back(image);
        resize(image, image, Size(0, 0), 0.5, 0.5, INTER_AREA);
    }
    return scaledimage;
}
Mat Orbfeaturedetector::descriptors(vector<KeyPoint> keypoints, vector<Mat> scaledimages, int seedvalue)
{
    float pi = 2 * acos(0);
    float sigma = 2;

    char name_[100];
    char addvalue[1] = {'a'};
    for (int j = 0; j < scaledimages.size(); j++)
    {

        GaussianBlur(scaledimages.at(j), scaledimages.at(j), Size(9, 9), sigma);
    }
    Mat image;
    int number_of_bits = 256;
    Mat descriptor = Mat::zeros(Size(int(number_of_bits / 8), keypoints.size()), CV_8U);
    srand(seedvalue);
    Point pattern[number_of_bits * 2];
    float S = 100;
    RNG rng(0x34985739);
    for (int i = 0; i < number_of_bits * 2; i++)
    {
        pattern[i].x = rng.uniform(-S / 2, S / 2);
        pattern[i].y = rng.uniform(-S / 2, S / 2);
    }
    for (int i = 0; i < keypoints.size(); i++)
    {
        KeyPoint keypoint = keypoints.at(i);

        int imagesize = keypoint.size / 10;
        Mat select_image;
        copyMakeBorder(scaledimages.at(imagesize - 1), select_image, S, S, S, S, BORDER_CONSTANT, Scalar(0));
        Point co_ordinate = Point(keypoint.pt.x / pow(2, (imagesize - 1)), keypoint.pt.y / pow(2, (imagesize - 1)));
        co_ordinate.x += S;
        co_ordinate.y += S;
        image = select_image(Rect(co_ordinate.x - int(S / 2), co_ordinate.y - int(S / 2), S, S));

        float angle = (360 - keypoint.angle) * pi / 180;
        int descriptorvalue = 0;

        float sigma1 = 0.04 * pow(S, 2);
        float sigma2 = 0.01 * pow(S, 2);
        Mat checkimage = Mat::zeros(Size(S, S), CV_32F);

        for (int n = 0; n < number_of_bits; n++)
        {
            // float u1 = ((float)rand() / (RAND_MAX)) < 0.0001 ? 0.0001 : ((float)rand() / (RAND_MAX));
            // float u2 = ((float)rand() / RAND_MAX);

            // int x1 = int(image.cols / 2 + sqrt(sigma1) * sqrt(-2 * log(u1)) * cos(2 * pi * u2));
            // int y1 = int(image.rows / 2 + sqrt(sigma1) * sqrt(-2 * log(u1)) * sin(2 * pi * u2));
            int x1 = cvRound(pattern[n].x * cos(angle) - pattern[n].y * sin(angle));
            int y1 = cvRound(pattern[n].x * sin(angle) + pattern[n].y * cos(angle));
            x1 += image.cols / 2;
            y1 += image.rows / 2;
            x1 = (x1 < 0) ? 0 : x1;
            x1 = (x1 >= image.cols) ? (image.cols - 1) : x1;
            y1 = (y1 < 0) ? 0 : y1;
            y1 = (y1 >= image.rows) ? (image.rows - 1) : y1;
            // u1 = ((float)rand() / RAND_MAX) < 0.0001 ? 0.0001 : ((float)rand() / RAND_MAX);
            // u2 = ((float)rand() / RAND_MAX);
            // int x2 = int(x1 + sqrt(sigma2) * sqrt(-2 * log(u1)) * cos(2 * pi * u2));
            // int y2 = int(y1 + sqrt(sigma2) * sqrt(-2 * log(u1)) * sin(2 * pi * u2));
            int x2 = cvRound(pattern[n + 1].x * cos(angle) - pattern[n + 1].y * sin(angle));
            int y2 = cvRound(pattern[n + 1].x * sin(angle) + pattern[n + 1].y * cos(angle));
            x2 += x1;
            y2 += y1;
            x2 = (x2 < 0) ? 0 : x2;
            x2 = (x2 >= image.cols) ? (image.cols - 1) : x2;
            y2 = (y2 < 0) ? 0 : y2;
            y2 = (y2 >= image.rows) ? (image.rows - 1) : y2;
            float px = image.at<float>(y1, x1);
            float py = image.at<float>(y2, x2);
            if (n % 8 == 0)
            {
                descriptorvalue = 0;
            }
            if (px > py)
            {
                descriptorvalue += pow(2, n % 8);
            }
            descriptor.at<uchar>(i, int(floor(n / 8))) = descriptorvalue;
            line(checkimage, Point(x1, y1), Point(x2, y2), Scalar(255));
        }
    }
    return descriptor;
}
vector<KeyPoint> Orbfeaturedetector::removekeypoints(vector<KeyPoint> keypointvect)
{
    vector<KeyPoint> newvectorkeypoint;
    float threshold = 0;
    if (keypointvect.size() <= 2)
    {
        return keypointvect;
    }
    for (int j = 0; j < (keypointvect.size() - 1); j++)
    {
        KeyPoint newkeypoint;
        if (keypointvect.at(j).response > threshold)
        {
            if (keypointvect.at(j).pt != keypointvect.at(j + 1).pt || keypointvect.at(j).angle != keypointvect.at(j + 1).angle)
            {

                newvectorkeypoint.push_back(keypointvect.at(j));
            }
        }
    }
    return newvectorkeypoint;
}
vector<KeyPoint> Orbfeaturedetector::Removekeypoint(vector<KeyPoint> keypoints, int numberofkeypoints)
{
    float threshold = 0.5;
    vector<KeyPoint> newkeypoints;
    if (keypoints.size() < numberofkeypoints)
    {
        numberofkeypoints = keypoints.size();
    }
    for (int i = 0; i < numberofkeypoints; i++)
    {

        newkeypoints.push_back(keypoints.at(i));
    }
    return newkeypoints;
}
vector<KeyPoint> Orbfeaturedetector::calculateorientation(vector<KeyPoint> keypoints, vector<Mat> scaledimages)
{
    KeyPoint keypoint;
    int n = 3;
    int x, y, constantvalue;
    float pi = 2 * acos(0);
    for (int i = 0; i < keypoints.size(); i++)
    {
        keypoint = keypoints.at(i);
        int imagesize = keypoint.size / 10;
        Mat image = scaledimages.at(imagesize - 1);
        Point co_ordinate = Point(keypoint.pt.x / pow(2, (imagesize - 1)), keypoint.pt.y / pow(2, (imagesize - 1)));
        float m00 = 0, m01 = 0, m10 = 0;
        for (int a = -n; a <= n; a++)
        {
            for (int b = -n; b <= n; b++)
            {
                x = co_ordinate.x + b;
                y = co_ordinate.y + a;
                if (x >= 0 && x < image.cols && y >= 0 && y < image.rows)
                {
                    m00 += image.at<float>(y, x);
                    m01 += a * image.at<float>(y, x);
                    m10 += b * image.at<float>(y, x);
                }
            }
        }
        int angle = atan2(m01, m10) * 180 / pi;

        while (abs(angle) > 360)
        {
            angle %= 360;
        }
        if (angle < 0)
        {
            angle = 360 + angle;
        }
        keypoints.at(i).angle = 360 - angle;
    }
    return keypoints;
}
tuple<vector<KeyPoint>, Mat> Orbfeaturedetector::featuresdetect(Mat initial_image)
{
    vector<KeyPoint> keypoints;
    Mat descriptor;
    float threshold = 0.1;
    vector<Mat> scaledimages = scalespace(initial_image, 4);
    Mat keypointsimage;
    int n = 3;
    int x = 0, y = 0;
    int constantvalue = 0;
    char name_[100];
    char toadd[1] = {'a'};
    float value_harris = 0.06;
    float dxx, dyy, dxy;
    for (int imageindex = 0; imageindex < scaledimages.size(); imageindex++)
    {
        Mat converted_image = scaledimages.at(imageindex);
        for (int i = n; i < converted_image.rows - n; i++)
        {
            for (int j = n; j < converted_image.cols - n; j++)
            {
                float thresholdvalue = 0;
                dxx = 0;
                dyy = 0;

                dxy = 0;
                if (converted_image.at<float>(i, j) > 0.03)
                {
                    int numberofpixels = 0;
                    x = 0;
                    y = 0;
                    float inputpixel = converted_image.at<float>(i, j);
                    numberofpixels += (threshold + inputpixel) < converted_image.at<float>(i, j - n) ? 1 : 0;
                    numberofpixels += (threshold + inputpixel) < converted_image.at<float>(i - n, j) ? 1 : 0;
                    numberofpixels += (threshold + inputpixel) < converted_image.at<float>(i, j + n) ? 1 : 0;
                    numberofpixels += (threshold + inputpixel) < converted_image.at<float>(i + n, j) ? 1 : 0;

                    if (numberofpixels >= 3)
                    {
                        numberofpixels = 0;
                        for (int k = -n; k <= n; k++)
                        {
                            x = j + k;
                            constantvalue = int(round(sqrt(abs(n * n - k * k))));
                            y = i + constantvalue;
                            if (x >= 0 && x < converted_image.cols && y >= 0 && y < converted_image.rows)
                            {
                                numberofpixels += (threshold + inputpixel) < converted_image.at<float>(y, x) ? 1 : 0;
                            }
                            y = i - constantvalue;
                            if (x >= 0 && x < converted_image.cols && y >= 0 && y < converted_image.rows)
                            {
                                numberofpixels += (threshold + inputpixel) < converted_image.at<float>(y, x) ? 1 : 0;
                            }
                        }
                        if (numberofpixels >= 12)
                        {

                            for (int height_part = -n; height_part < n; height_part++)
                            {
                                for (int width_part = -n; width_part < n; width_part++)
                                {
                                    float dx = 0.5 * (converted_image.at<float>(i + height_part, j + width_part + 1) - converted_image.at<float>(i + height_part, j + width_part - 1));
                                    float dy = 0.5 * (converted_image.at<float>(i + height_part + 1, j + width_part) - converted_image.at<float>(i + height_part - 1, j + width_part));
                                    dxx += dx * dx;
                                    dyy += dy * dy;
                                    dxy += dx * dy;
                                    // dxx += (converted_image.at<float>(i + height_part, j + width_part + 1) - 2 * converted_image.at<float>(i + height_part, j + width_part) + converted_image.at<float>(i + height_part, j + width_part - 1));
                                    // dyy += (converted_image.at<float>(i + height_part + 1, j + width_part) - 2 * converted_image.at<float>(i + height_part, j + width_part) + converted_image.at<float>(i + height_part - 1, j + width_part));
                                    // dxy += 0.25 * (converted_image.at<float>(i + height_part + 1, j + width_part + 1) - converted_image.at<float>(i + height_part + 1, j + width_part - 1) - converted_image.at<float>(i + height_part - 1, j + width_part + 1) + converted_image.at<float>(i + height_part - 1, j + width_part - 1));
                                }
                            }
                            float alpha = value_harris * pow((dxx + dyy), 2);
                            float beta = (dxx * dyy) - dxy * dxy;
                            float R = (beta)-alpha;
                            // keypointsimage.at<float>(i * pow(2, imageindex), j * pow(2, imageindex)) = 255;
                            KeyPoint keypoint;
                            keypoint.pt = Point(j * pow(2, imageindex), i * pow(2, imageindex));
                            float scale = 1.f / ((1 << 2) * 7);
                            float scale_sq_sq = scale * scale * scale * scale;
                            keypoint.size = (imageindex + 1) * 10;
                            keypoint.response = R * scale_sq_sq;
                            keypoints.push_back(keypoint);
                        }
                    }
                    else
                    {
                        numberofpixels = 0;
                        numberofpixels += (-threshold + inputpixel) > converted_image.at<float>(i, j - n) ? 1 : 0;
                        numberofpixels += (-threshold + inputpixel) > converted_image.at<float>(i - n, j) ? 1 : 0;
                        numberofpixels += (-threshold + inputpixel) > converted_image.at<float>(i, j + n) ? 1 : 0;
                        numberofpixels += (-threshold + inputpixel) > converted_image.at<float>(i + n, j) ? 1 : 0;
                        if (numberofpixels >= 3)
                        {
                            numberofpixels = 0;
                            for (int k = -n; k <= n; k++)
                            {
                                x = j + k;
                                constantvalue = int(round(sqrt(abs(n * n - k * k))));
                                y = i + constantvalue;
                                if (x >= 0 && x < converted_image.cols && y >= 0 && y < converted_image.rows)
                                {
                                    numberofpixels += (-threshold + inputpixel) > converted_image.at<float>(y, x) ? 1 : 0;
                                }

                                y = i - constantvalue;
                                if (x >= 0 && x < converted_image.cols && y >= 0 && y < converted_image.rows)
                                {
                                    numberofpixels += (-threshold + inputpixel) > converted_image.at<float>(y, x) ? 1 : 0;
                                }
                            }
                            if (numberofpixels >= 12)
                            {

                                for (int height_part = -n; height_part <= n; height_part++)
                                {
                                    for (int width_part = -n; width_part <= n; width_part++)
                                    {
                                        float dx = 0.5 * (converted_image.at<float>(i + height_part, j + width_part + 1) - converted_image.at<float>(i + height_part, j + width_part - 1));
                                        float dy = 0.5 * (converted_image.at<float>(i + height_part + 1, j + width_part) - converted_image.at<float>(i + height_part - 1, j + width_part));
                                        dxx += dx * dx;
                                        dyy += dy * dy;
                                        dxy += dx * dy;
                                        // dxx += (converted_image.at<float>(i + height_part, j + width_part + 1) - 2 * converted_image.at<float>(i + height_part, j + width_part) + converted_image.at<float>(i + height_part, j + width_part - 1));
                                        // dyy += (converted_image.at<float>(i + height_part + 1, j + width_part) - 2 * converted_image.at<float>(i + height_part, j + width_part) + converted_image.at<float>(i + height_part - 1, j + width_part));
                                        // dxy += 0.25 * (converted_image.at<float>(i + height_part + 1, j + width_part + 1) - converted_image.at<float>(i + height_part + 1, j + width_part - 1) - converted_image.at<float>(i + height_part - 1, j + width_part + 1) + converted_image.at<float>(i + height_part - 1, j + width_part - 1));
                                    }
                                }
                                float alpha = value_harris * pow((dxx + dyy), 2);
                                float beta = (dxx * dyy) - dxy * dxy;
                                float R = (beta)-alpha;
                                // keypointsimage.at<float>(i * pow(2, imageindex), j * pow(2, imageindex)) = 255;
                                KeyPoint keypoint;
                                keypoint.pt = Point(j * pow(2, imageindex), i * pow(2, imageindex));
                                float scale = 1.f / ((1 << 2) * 7);
                                float scale_sq_sq = scale * scale * scale * scale;
                                keypoint.size = (imageindex + 1) * 10;
                                keypoint.response = R * scale_sq_sq;
                                keypoints.push_back(keypoint);
                            }
                        }
                    }
                }
            }
        }
    }
    sort(keypoints.begin(), keypoints.end(), sortkeypoint);
    vector<KeyPoint> newkeypoints;
    newkeypoints = removekeypoints(keypoints);
    sort(keypoints.begin(), keypoints.end(), sortResponse);
    newkeypoints = Removekeypoint(keypoints, keypointdisplay);
    newkeypoints = calculateorientation(newkeypoints, scaledimages);
    descriptor = descriptors(newkeypoints, scaledimages, keypointdisplay);
    // imshow("window show keypoints", keypointsimage);
    return make_tuple(newkeypoints, descriptor);
}