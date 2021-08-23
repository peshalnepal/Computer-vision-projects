#include"ImageRotation.h"

ImageRotation::ImageRotation() {

}

int *ImageRotation::getoutputwidthheight()
{
    /**
     * This function is used calculated final width and height of the output image
     */
    int originx = (int) (x / 2);
    int originy = (int) (y / 2);
    int centrevaluex, centrevaluey;
    static int value[2];
    if (rotationdirection = true)
    {
        centrevaluex = int(cos(radianangle) * (0 - originx) - sin(radianangle) * (0 - originy));
        centrevaluex = int(((cos(radianangle) * (x - originx) - sin(radianangle) * (0 - originy)) >= centrevaluex) ? (cos(radianangle) * (x - originx) - sin(radianangle) * (0 - originy)) : centrevaluex);
        centrevaluex = int(((cos(radianangle) * (x - originx) - sin(radianangle) * (y - originy)) >= centrevaluex) ? (cos(radianangle) * (x - originx) - sin(radianangle) * (y - originy)) : centrevaluex);
        centrevaluex = int(((cos(radianangle) * (0 - originx) - sin(radianangle) * (y - originy)) >= centrevaluex) ? (cos(radianangle) * (0 - originx) - sin(radianangle) * (y - originy)) : centrevaluex);
        value[0] = centrevaluex * 2 + 1;
        centrevaluey = int(sin(radianangle) * (0 - originx) + cos(radianangle) * (0 - originy));
        centrevaluey = int(((sin(radianangle) * (x - originx) + cos(radianangle) * (0 - originy)) >= centrevaluey) ? (sin(radianangle) * (x - originx) + cos(radianangle) * (0 - originy)) : centrevaluey);
        centrevaluey = int(((sin(radianangle) * (x - originx) + cos(radianangle) * (y - originy)) >= centrevaluey) ? (sin(radianangle) * (x - originx) + cos(radianangle) * (y - originy)) : centrevaluey);
        centrevaluey = int(((sin(radianangle) * (0 - originx) + cos(radianangle) * (y - originy)) >= centrevaluey) ? (sin(radianangle) * (0 - originx) + cos(radianangle) * (y - originy)) : centrevaluey);
        value[1] = centrevaluey * 2 + 1;
    }
    else
    {
        centrevaluex = int(cos(radianangle) * (0 - originx) + sin(radianangle) * (0 - originy));
        centrevaluex = int(((cos(radianangle) * (x - originx) + sin(radianangle) * (0 - originy)) >= centrevaluex) ? (cos(radianangle) * (x - originx) + sin(radianangle) * (0 - originy)) : centrevaluex);
        centrevaluex = int(((cos(radianangle) * (x - originx) + sin(radianangle) * (y - originy)) >= centrevaluex) ? (cos(radianangle) * (x - originx) + sin(radianangle) * (y - originy)) : centrevaluex);
        centrevaluex = int(((cos(radianangle) * (0 - originx) + sin(radianangle) * (y - originy)) >= centrevaluex) ? (cos(radianangle) * (0 - originx) + sin(radianangle) * (y - originy)) : centrevaluex);
        value[0] = centrevaluex * 2 + 1;
        centrevaluey = int(-sin(radianangle) * (0 - originx) + cos(radianangle) * (0 - originy));
        centrevaluey = int(((-sin(radianangle) * (x - originx) + cos(radianangle) * (0 - originy)) >= centrevaluey) ? (-sin(radianangle) * (x - originx) + cos(radianangle) * (0 - originy)) : centrevaluey);
        centrevaluey = int(((-sin(radianangle) * (x - originx) + cos(radianangle) * (y - originy)) >= centrevaluey) ? (-sin(radianangle) * (x - originx) + cos(radianangle) * (y - originy)) : centrevaluey);
        centrevaluey = int(((-sin(radianangle) * (0 - originx) + cos(radianangle) * (y - originy)) >= centrevaluey) ? (-sin(radianangle) * (0 - originx) + cos(radianangle) * (y - originy)) : centrevaluey);
        value[1] = centrevaluey * 2 + 1;
    }
    return value;
}

Mat ImageRotation::imagerotationalgorithm(Mat image, int angle, bool clockwise)
{
    /**
     * This function is responsible for rotating the image in required angle and direction using
     *  Rotation by Area Mapping algorithm
     */
    Mat imageclone = image.clone();
    radianangle = pi / 180 * angle;
    y = (image).rows;
    x = (image).cols;
    int originx = (int) (x / 2);
    int originy = (int) (y / 2);
    int *value;
    value = getoutputwidthheight();
    image = Mat::zeros(Size(*(value + 0), *(value + 1)), CV_8UC3);
    float x1 = 0;
    float y1 = 0;
    float comparex1;
    float comparey1;
    float weight = 1;
    float fractionx, fractiony;
    Vec3f outputvalue;
    int centrevaluex = (*(value + 0) - 1) / 2;
    int centrevaluey = (*(value + 1) - 1) / 2;
    for (int i = 0; i < *(value + 1); i++)
    {
        for (int j = 0; j < *(value + 0); j++)
        {
            /**
             * calculating source pixel for respective destination pixel
             **/

            if (clockwise == true)
            {
                x1 = (j - centrevaluex - 1) * cos(radianangle) + (i - centrevaluey) * sin(radianangle);
                y1 = -(j - centrevaluex) * sin(radianangle) + (i - centrevaluey) * cos(radianangle);

            }
            else
            {
                x1 = (j - centrevaluex) * cos(radianangle) - (i - centrevaluey) * sin(radianangle);
                y1 = (j - centrevaluex) * sin(radianangle) + (i - centrevaluey) * cos(radianangle);
            }
            x1 = x1 + originx + 1;
            y1 = y1 + originy + 1;
            /**
             * if obtained source pixels coordinate lies inside the given width and height of the image
             * then calculate destination pixel value using nearest four of the source pixel from the
             * obtained source pixel value
             **/
            if ((x1 >= 0 && x1 < (x - 1)) && (y1 >= 0 && y1 < (y - 1)))
            {
                fractionx = abs((x1 - (int) x1));
                fractiony = abs((y1 - (int) y1));
                outputvalue = (weight - fractionx) * (weight - fractiony) * imageclone.at<Vec3b>(int(y1), int(x1));
                outputvalue += (fractionx) * (weight - fractiony) * imageclone.at<Vec3b>(int(y1), int(x1) + 1);
                outputvalue += (weight - fractionx) * (fractiony) * imageclone.at<Vec3b>(int(y1) + 1, int(x1));
                outputvalue += (fractionx) * (fractiony) * imageclone.at<Vec3b>(int(y1) + 1, int(x1) + 1);
                image.at<Vec3b>(i, j) = (Vec3b) outputvalue;
            }
        }
    }

    return image;
}

