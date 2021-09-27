#include "../include/featuredetect.h"

Mat FeatrueDetect::createMat3Drix(Mat imagearray[3], int x, int y)
{
  int dims[] = {3, 3, 3};
  Mat Mat3D(3, dims, CV_32F, Scalar::all(0));
  for (int i = 0; i < Mat3D.size[0]; i++)
  {
    for (int k = 0; k < Mat3D.size[1]; k++)
    {
      for (int j = 0; j < Mat3D.size[2]; j++)
      {
        Mat3D.at<float>(i, k, j) = imagearray[i].at<float>(y + k - 1, x + j - 1) / 255;
      }
    }
  }
  return Mat3D;
}

vector<KeyPoint> FeatrueDetect::removekeypoints(vector<KeyPoint> keypointvect)
{
  vector<KeyPoint> newvectorkeypoint;
  if (keypointvect.size() <= 2)
  {
    return keypointvect;
  }
  for (int j = 0; j < (keypointvect.size() - 1); j++)
  {
    KeyPoint newkeypoint;
    if (keypointvect.at(j).pt != keypointvect.at(j + 1).pt && keypointvect.at(j).angle != keypointvect.at(j + 1).angle && keypointvect.at(j).response != keypointvect.at(j + 1).response)
    {
      newvectorkeypoint.push_back(keypointvect.at(j));
    }
  }
  return newvectorkeypoint;
}

/** 
 * This is function which create descriptor for each keypoint . 
 * The descriptor does not depend upon scale and orientation and thats need to be take into consideration.
 */
Mat FeatrueDetect::create_descripter(vector<KeyPoint> keypoints_, vector<vector<Mat>> imagevec)
{
  Mat finaloutput = Mat::zeros(Size(128, keypoints_.size()), CV_32F);
  vector<float> row_bin_list, col_bin_list, magnitude_list, orientation_bin_list;
  int window_width = 4;
  int scale_weighter = 3;
  for (int kv = 0; kv < int(keypoints_.size()); kv++)
  {
    row_bin_list.clear();
    col_bin_list.clear();
    magnitude_list.clear();
    orientation_bin_list.clear();
    float pi = 2 * acos(0);
    int octave = ((keypoints_.at(kv)).octave) & 255;
    int layer = ((keypoints_.at(kv)).octave >> 8) & 255;
    float scale = 1 / pow(2, octave);
    Mat image = (imagevec.at(octave)).at(layer);
    int image_width = image.cols;
    int image_height = image.rows;
    resize(image, image, Size(int(image_width / 2), int(image_height / 2)), 0, 0, INTER_NEAREST);
    image_width = image.cols;
    image_height = image.rows;
    float hist_width = scale_weighter * 0.5 * scale * (keypoints_.at(kv)).size;
    int half_width = int(round(hist_width * sqrt(2) * (window_width + 1) * 0.5));
    int imagediagonal = int(sqrt(pow(image_width, 2) + pow(image_height, 2)));
    if (half_width >= imagediagonal)
    {
      half_width = imagediagonal;
    }
    int nbins = 8;
    float angle = (keypoints_.at(kv)).angle;
    float cos_value = cos(angle * pi / 180);
    float sin_value = sin(angle * pi / 180);
    float weight_multiplier = -0.5 / (pow((0.5 * window_width), 2));
    Point key_points = Point(int((keypoints_.at(kv)).pt.x * scale), int((keypoints_.at(kv)).pt.y * scale));
    int dims[] = {nbins, window_width + 2, window_width + 2};
    Mat histogram_(3, dims, CV_32F, Scalar::all(0));
    for (int i = -half_width; i <= half_width; i++)
    {
      for (int j = -half_width; j <= half_width; j++)
      {
        float col_rot = cos_value * j - sin_value * i;
        float row_rot = sin_value * j + cos_value * i;
        float row_bin = (row_rot / hist_width) + 0.5 * window_width - 0.5;
        float col_bin = (col_rot / hist_width) + 0.5 * window_width - 0.5;
        if (row_bin > -1 && row_bin < window_width && col_bin > -1 && col_bin < window_width)
        {
          int window_row = int(round(key_points.y + i));
          int window_col = int(round(key_points.x + j));
          if (window_row > 0 && window_row < (image_height - 1) && window_col > 0 && window_col < (image_width - 1))
          {
            float Gx = (image.at<float>(window_row, window_col + 1) - image.at<float>(window_row, window_col - 1));
            float Gy = (image.at<float>(window_row + 1, window_col) - image.at<float>(window_row - 1, window_col));
            float Gvalue = sqrt(Gx * Gx + Gy * Gy);
            float Gangle;
            if ((atan2(Gy, Gx) * 180 / pi) < 0)
            {
              Gangle = (atan2(Gy, Gx) * 180 / pi) + 360 * floor(abs(atan2(Gy, Gx) * 180 / pi) / 360);
            }
            else
            {
              Gangle = (atan2(Gy, Gx) * 180 / pi) - 360 * floor((atan2(Gy, Gx) * 180 / pi) / 360);
            }
            if (Gangle < 0)
            {
              Gangle += 360;
            }
            float weight = exp(weight_multiplier * (pow((row_rot / hist_width), 2) + pow((col_rot / hist_width), 2)));
            row_bin_list.push_back(row_bin);
            col_bin_list.push_back(col_bin);
            magnitude_list.push_back((weight * Gvalue));
            orientation_bin_list.push_back(((Gangle - angle) * nbins / 360));
          }
        }
      }
    }
    for (int k = 0; k < magnitude_list.size(); k++)
    {
      int rows_bin_floor = floor(row_bin_list.at(k));
      int columns_bin_floor = floor(col_bin_list.at(k));
      int orientation_bin_floor = floor(orientation_bin_list.at(k));
      float magnitude_value = magnitude_list.at(k);
      if (orientation_bin_floor < 0)
      {
        orientation_bin_floor += nbins;
      }
      if (orientation_bin_floor >= nbins)
      {
        orientation_bin_floor -= nbins;
      }
      
      
      //Smoothing via trilinear interpolation
      //Notations follows https://en.wikipedia.org/wiki/Trilinear_interpolation
      // Note that we are really doing the inverse of trilinear interpolation here (we take the center value of the cube and distribute it among its eight neighbors)
      
      
      if (rows_bin_floor < 4 && columns_bin_floor < 4 && (orientation_bin_floor >= 0 && orientation_bin_floor < nbins))
      {
        float c1 = magnitude_value * (row_bin_list.at(k) - rows_bin_floor);
        float c0 = magnitude_value * (1 - (row_bin_list.at(k) - rows_bin_floor));
        float c11 = c1 * (col_bin_list.at(k) - columns_bin_floor);
        float c10 = c1 * (1 - (col_bin_list.at(k) - columns_bin_floor));
        float c01 = c0 * (col_bin_list.at(k) - columns_bin_floor);
        float c00 = c0 * (1 - (col_bin_list.at(k) - columns_bin_floor));
        float c111 = c11 * (orientation_bin_list.at(k) - orientation_bin_floor);
        float c110 = c11 * (1 - (orientation_bin_list.at(k) - orientation_bin_floor));
        float c101 = c10 * (orientation_bin_list.at(k) - orientation_bin_floor);
        float c100 = c10 * (1 - (orientation_bin_list.at(k) - orientation_bin_floor));
        float c011 = c01 * (orientation_bin_list.at(k) - orientation_bin_floor);
        float c010 = c01 * (1 - (orientation_bin_list.at(k) - orientation_bin_floor));
        float c001 = c00 * (orientation_bin_list.at(k) - orientation_bin_floor);
        float c000 = c00 * (1 - (orientation_bin_list.at(k) - orientation_bin_floor));
        histogram_.at<float>(orientation_bin_floor, rows_bin_floor + 1, columns_bin_floor + 1) += c000;
        histogram_.at<float>(((orientation_bin_floor + 1) % nbins), rows_bin_floor + 1, columns_bin_floor + 1) += c001;
        histogram_.at<float>(orientation_bin_floor, rows_bin_floor + 1, columns_bin_floor + 2) += c010;
        histogram_.at<float>(((orientation_bin_floor + 1) % nbins), rows_bin_floor + 1, columns_bin_floor + 2) += c011;
        histogram_.at<float>(orientation_bin_floor, rows_bin_floor + 2, columns_bin_floor + 1) += c100;
        histogram_.at<float>(((orientation_bin_floor + 1) % nbins), rows_bin_floor + 2, columns_bin_floor + 1) += c101;
        histogram_.at<float>(orientation_bin_floor, rows_bin_floor + 2, columns_bin_floor + 2) += c110;
        histogram_.at<float>(((orientation_bin_floor + 1) % nbins), rows_bin_floor + 2, columns_bin_floor + 2) += c111;
      }
    }
    float normalized_value = norm(histogram_);
    float threshold_value = normalized_value * 0.2;
    int finalshape = window_width * window_width * nbins;
    for (int checkint1 = 1; checkint1 <= (window_width); checkint1++)
    {
      for (int checkint2 = 1; checkint2 <= (window_width); checkint2++)
      {
        for (int checkint = 0; checkint < nbins; checkint++)
        {
          finaloutput.at<float>(kv, (checkint + nbins * (checkint2 - 1) + nbins * window_width * (checkint1 - 1))) = histogram_.at<float>(checkint, checkint1, checkint2);
          if (finaloutput.at<float>(kv, (checkint + nbins * (checkint2 - 1) + nbins * window_width * (checkint1 - 1))) > threshold_value)
          {
            finaloutput.at<float>(kv, (checkint + nbins * (checkint2 - 1) + nbins * window_width * (checkint1 - 1))) = threshold_value;
          }
        }
      }
    }
  }
  finaloutput /= max(norm(finaloutput), 0.00001);
  finaloutput = (512 * finaloutput);
  threshold(-finaloutput, finaloutput, 0, 0, THRESH_TRUNC);
  finaloutput = -finaloutput;
  threshold(finaloutput, finaloutput, 255, 255, THRESH_TRUNC);
  return finaloutput;
}

/**
 * This function generate sigma value for Gaussian blur for images in each octave.
 */ 
vector<float> FeatrueDetect::calculatesigmavalue(float sigma, int number_of_intervals)
{
  vector<float> calculatedsigma;
  calculatedsigma.push_back(sigma);
  float k = pow(2, .5);

  for (int i = 1; i < (number_of_intervals + 3); i++)
  {
    float sigma_previous = pow(k, (i - 1)) * sigma;
    float sigma_total = k * sigma_previous;
    float sigma_value = sqrt(pow(sigma_total, 2) - pow(sigma_previous, 2));
    calculatedsigma.push_back(sigma_value);
  }
  return calculatedsigma;
}


/**
 * This function generate image pyramid based  on supplied octave value , 
 * initial sigma value for each octave and number of intervals in each octave.
 */ 

vector<vector<Mat>> FeatrueDetect::createblurimage(Mat image, float sigma, int num_intervals, int octave)
{
  int width_, height_;
  vector<vector<Mat>> imagevec;
  vector<Mat> Group_of_images;
  int number_of_images_each_octave = num_intervals + 3;
  vector<float> sigmavalue;
  sigmavalue = calculatesigmavalue(sigma, num_intervals);
  for (int i = 0; i < octave; i++)
  {
    Mat image1;
    for (int j = 0; j < number_of_images_each_octave; j++)
    {
      GaussianBlur(image, image1, Size(0, 0), sigmavalue.at(j));
      Group_of_images.push_back(image1.clone());
    }
    imagevec.push_back(Group_of_images);
    Group_of_images.clear();
    width_ = image.cols;
    height_ = image.rows;
    resize(image, image, Size((int)width_ / 2, (int)height_ / 2), 0, 0, INTER_NEAREST);
  }
  return imagevec;
}

/**
 * This function subtact images of different scales and generate Difference of Gaussian. 
  */ 

vector<vector<Mat>> FeatrueDetect::DifferenceofGaussianimg(vector<vector<Mat>> blurredimage)
{
  vector<Mat> Group_of_images;
  vector<Mat> Group_of_diff_images;
  vector<vector<Mat>> DOGimages;
  for (int octave_ = 0; octave_ < blurredimage.size(); octave_++)
  {
    Group_of_images = blurredimage.at(octave_);

    for (int size_ = 0; size_ < (Group_of_images.size() - 1); size_++)
    {
      Mat imagecheck1 = Group_of_images.at(size_).clone();
      Mat imagecheck2 = Group_of_images.at(size_ + 1).clone();
      Mat diffimg;
      imagecheck1.convertTo(imagecheck1, CV_32F);
      imagecheck2.convertTo(imagecheck2, CV_32F);
      diffimg = (-imagecheck1 + imagecheck2);
      Group_of_diff_images.push_back(diffimg.clone());
    }
    DOGimages.push_back(Group_of_diff_images);
    Group_of_images.clear();
    Group_of_diff_images.clear();
  }
  return DOGimages;
}


/** This function takes keypoints and image pyramid containind image blurred in different scale 
 * and find orientation for each keypoint
*/
vector<KeyPoint> FeatrueDetect::calculateorientation(vector<KeyPoint> keypoints, vector<vector<Mat>> imagevec_cpy)
{
  float pi = 2 * acos(0);
  vector<KeyPoint> keypoints_orientation;
  for (int i = 0; i < keypoints.size(); i++)
  {
    KeyPoint keypoint = keypoints.at(i);
    float octave_ = keypoint.octave & 255;
    float layer = (keypoint.octave >> 8) & 255;
    int xx_axis = keypoint.pt.x;
    int yy_axis = keypoint.pt.y;
    float scale = 1.5;
    float radius_factor = 3;
    int nbins = 36;
    Mat histogramcontainer = Mat::zeros(Size(nbins, 1), CV_32F);
    Mat smoothhistogram = Mat::zeros(Size(nbins, 1), CV_32F);
    float circularwindowsigma = scale * keypoint.size / pow(2, octave_ + 1);
    int radius = int(round(radius_factor * circularwindowsigma));
    float weight_factor = -0.5 / pow(circularwindowsigma, 2);
    float weight;
    Mat checkimageoreint = imagevec_cpy.at(octave_).at(layer);
    checkimageoreint.convertTo(checkimageoreint, CV_32F);
    for (int p = -radius; p < radius + 1; p++)
    {
      float region_y = yy_axis + p;
      if (region_y > 0 && region_y < checkimageoreint.rows - 1)
      {
        for (int q = -radius; q < radius + 1; q++)
        {
          float region_x = xx_axis + q;
          if (region_x > 0 && region_x < checkimageoreint.cols - 1)
          {

            float Gx = (checkimageoreint.at<float>(region_y, region_x + 1) - checkimageoreint.at<float>(region_y, region_x - 1));
            float Gy = (checkimageoreint.at<float>(region_y - 1, region_x) - checkimageoreint.at<float>(region_y + 1, region_x));
            float Gvalue = sqrt(pow(Gx, 2) + pow(Gy, 2));
            float angle;
            if ((atan2(Gy, Gx) * 180 / pi) < 0)
            {
              angle = (atan2(Gy, Gx) * 180 / pi) + 360 * floor(abs(atan2(Gy, Gx) * 180 / pi) / 360);
            }
            else
            {
              angle = (atan2(Gy, Gx) * 180 / pi) - 360 * floor((atan2(Gy, Gx) * 180 / pi) / 360);
            }
            if (angle < 0)
            {
              angle = 360 + angle;
            }
            weight = exp(weight_factor * (p * p + q * q));
            histogramcontainer.at<float>(0, (int)(round(angle / 10))) = histogramcontainer.at<float>(0, (int)(round(angle / 10))) + weight * Gvalue;
          }
        }
      }
    }

    for (int scontainer = 0; scontainer < nbins; scontainer++)
    {
      int minvalu1 = (scontainer - 1) < 0 ? (nbins + (scontainer - 1)) : (scontainer - 1);
      int minvalu2 = (scontainer - 2) < 0 ? (nbins + (scontainer - 2)) : (scontainer - 2);
      smoothhistogram.at<float>(0, scontainer) = (6 * histogramcontainer.at<float>(0, scontainer) + 4 * (histogramcontainer.at<float>(0, minvalu1) + histogramcontainer.at<float>(0, (scontainer + 1) % nbins)) + histogramcontainer.at<float>(0, minvalu2) + histogramcontainer.at<float>(0, (scontainer + 2) % nbins)) / 16;
    }
    Point Maxvalue;
    Point Minvalue;
    double min_, max_;
    minMaxLoc(smoothhistogram, &min_, &max_, &Minvalue, &Maxvalue);
    float peak_ratio = 0.8;
    for (int scontainer = 0; scontainer < nbins; scontainer++)
    {
      int minvalue = (scontainer - 1) < 0 ? (nbins + (scontainer - 1)) : (scontainer - 1);
      if (smoothhistogram.at<float>(0, scontainer) >= (peak_ratio * max_))
      {
        // Quadratic peak interpolation
        // The interpolation update is given by equation (6.30) in https://ccrma.stanford.edu/~jos/sasp/Quadratic_Interpolation_Spectral_Peaks.html
        float left_value = smoothhistogram.at<float>(0, minvalue);
        float right_value = histogramcontainer.at<float>(0, (scontainer + 1) % nbins);
        int interpolated_peak_index = int((scontainer) + 0.5 * (left_value - right_value) / (left_value - 2 * smoothhistogram.at<float>(0, scontainer) + right_value)) % nbins;
        float orientation = (interpolated_peak_index)*360. / nbins;
        if (abs(orientation) < 0.0001)
        {
          orientation = 0;
        }
        KeyPoint newkeypoint;
        keypoint.pt = Point(int(xx_axis * 0.5 * pow(2, octave_)), int(yy_axis * 0.5 * pow(2, octave_)));
        keypoint.size *= 0.5;
        newkeypoint = KeyPoint(keypoint.pt, keypoint.size, (360 - orientation), keypoint.response, keypoint.octave, keypoint.class_id);
        keypoints_orientation.push_back(newkeypoint);
      }
    }
  }
  return keypoints_orientation;
}

/** This function Read Image and determine the keypoints and passes the determine keypoint to other 
 * function to determine orientation of keypoint and obtain the descriptor
*/
tuple<vector<KeyPoint>, Mat> FeatrueDetect::featuresdetect(Mat image)
{
  vector<Mat> final_descriptor;
  float pi = 2 * acos(0);
  vector<vector<Mat>> imagevec;
  vector<vector<Mat>> imagevec_cpy;
  vector<Mat> Group_of_images;
  vector<vector<Mat>> DoGs;
  vector<Mat> Image_orientntation;
  vector<KeyPoint> keypoints_orientation;
  image.convertTo(image, CV_32F);
  float sigma = 2.5;
  int num_intervals = 3;
  resize(image, image, Size(0, 0), 2, 2, INTER_LINEAR);
  imagevec = createblurimage(image, sigma, num_intervals, 3);
  DoGs = DifferenceofGaussianimg(imagevec);
  int octave_ = 0;
  for (octave_ = 0; octave_ < DoGs.size(); octave_++)
  {
    Group_of_images = DoGs.at(octave_);
    Image_orientntation = imagevec.at(octave_);

    for (int i = 1; i < (Group_of_images.size() - 1); i++)
    {
      Mat outputimage;
      for (int a = 2; a < ((Group_of_images.at(i)).rows - 2); a++)
      {
        for (int b = 2; b < ((Group_of_images.at(i)).cols - 2); b++)
        {

          int xx_axis = b;
          int yy_axis = a;
          float compared_value = (Group_of_images.at(i)).at<float>(yy_axis, xx_axis);
          compared_value /= 255;
          float threshold_value = (int)floor(0.5 * 0.04 / num_intervals) * 255;
          if (abs(compared_value) >= 0.04 && abs(compared_value) != 0)
          {
            Mat imgarray[3] = {Group_of_images.at(i - 1), Group_of_images.at(i), Group_of_images.at(i + 1)};
            Mat Mat3D = createMat3Drix(imgarray, b, a);
            int minInd[3];
            int maxInd[3];
            double min, max;
            minMaxIdx(Mat3D, &min, &max, minInd, maxInd, Mat());
            if (compared_value == min || compared_value == max)
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
              int value = i;
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
                h = -((Hx.clone()).inv()) * Dx;
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
                if (xx_axis < 0 || xx_axis >= Group_of_images.at(i).cols || yy_axis < 0 || yy_axis >= Group_of_images.at(i).rows || value < 0 || value >= Group_of_images.size())
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
                if (abs(D_) * num_intervals >= 0.04)
                {
                  float alpha = pow((dxx + dyy), 2);
                  float beta = (dxx * dyy) - dxy * dxy;
                  float eigenratio = 10;
                  if (beta > 0 && (alpha * eigenratio) < (beta * pow((eigenratio + 1), 2)))
                  {
                    KeyPoint keypoint = KeyPoint();
                    keypoint.pt = Point(xx_axis, yy_axis);
                    keypoint.octave = octave_ + value * pow(2, 8) + int(round(((h.at<float>(2, 0)) + 0.5) * 255)) * pow(2, 16);
                    keypoint.size = sigma * pow(2, (value + h.at<float>(2, 0)) / num_intervals) * pow(2, octave_ + 1);
                    keypoint.response = abs(D_);
                    keypoints_orientation.push_back(keypoint);
                  }
                }
              }
            }
          }
        }
      }
    }
    Group_of_images.clear();
  }
  keypoints_orientation = calculateorientation(keypoints_orientation, imagevec);
  sort(keypoints_orientation.begin(), keypoints_orientation.end(), sortkeypoint);
  vector<KeyPoint> newkeypoints;
  newkeypoints = removekeypoints(keypoints_orientation);
  Mat describe = create_descripter(newkeypoints, imagevec);
  return make_tuple(newkeypoints, describe);
}