#include "../include/imagetostl.h"

vector<Mat> ImageToStl::sortimages(vector<Mat> images)
{
 sort(images.begin(),images.end(),sortbypixels);
return images;
}