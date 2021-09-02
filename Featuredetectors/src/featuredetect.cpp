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
vector<KeyPoint> FeatrueDetect::sortkeypoints(vector<KeyPoint> keypointvect)
{
  vector<KeyPoint> newvectorkeypoint;
  if (keypointvect.size() <= 2)
  {
    return keypointvect;
  }
  for (int j = 0; j < keypointvect.size(); j++)
  {
    KeyPoint newkeypoint;
    for (int i = (j + 1); i < (keypointvect.size()); i++)
    {
      if (keypointvect.at(j).pt.x != keypointvect.at(i).pt.x || keypointvect.at(j).pt.y != keypointvect.at(i).pt.y)
      {
        newvectorkeypoint.push_back(keypointvect.at(j));
      }
      else
      {
        keypointvect.erase(keypointvect.begin() + i);
        i--;
        if (i < 0)
        {
          i = 0;
        }
      }
    }
  }
  return newvectorkeypoint;
}
vector<float> FeatrueDetect::descripter(Mat image_, int x, int y)
{
  float pi = 2 * acos(0);
  vector<float> container;
  float variab[128] = {0};
  resize(image_, image_, Size(128, 128), INTER_AREA);
  copyMakeBorder(image_, image_, 9, 9, 9, 9, BORDER_REPLICATE);
  int i = 0;
  for (int a = -8; a < 8; a + 4)
  {
    for (int b = -8; b < 8; b + 4)
    {

      for (int c = 0; c < 4; c++)
      {
        for (int d = 0; d < 4; b)
        {
          int x_axis = x + b + d;
          int y_axis = y + a + c;
          float Gx = image_.at<float>(y_axis, x_axis + 1) - image_.at<float>(y_axis, x_axis - 1);
          float Gy = image_.at<float>(y_axis + 1, x_axis) - image_.at<float>(y_axis - 1, x_axis);
          float Gvalue = sqrt(pow(Gx, 2) + pow(Gy, 2));
          float angle = atan2(Gy, Gx) * 180 / pi;
          if (angle < 0)
          {
            angle = 360 + angle;
          }
          variab[i * 8 + (int)angle / 45] += Gvalue;
        }
      }
      i++;
      // container.push_back(variab);
    }
  }
  for (int j = 0; j < 4; j++)
  {
    float sum = 0;
    for (int k = 0; k < 32; k++)
    {
      sum += pow(variab[32 * j + k], 2);
    }
    for (int l = 0; l < 32; l++)
    {
      variab[32 * j + l] = variab[32 * j + l] / sum;
    }
  }

  container.assign(begin(variab), end(variab));
  return container;
}
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
    cout << sigma_value << endl;
    calculatedsigma.push_back(sigma_value);
  }
  return calculatedsigma;
}
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
vector<KeyPoint> FeatrueDetect::featuresdetect(Mat image)
{
  float pi = 2 * acos(0);
  vector<vector<Mat>> imagevec;
  vector<vector<Mat>> imagevec_cpy;
  vector<Mat> Group_of_images;
  vector<Mat> Group_of_diff_images;
  vector<vector<Mat>> DoGs;
  vector<Mat> Image_orientntation;
  vector<KeyPoint> keypoints_orientation;
  Mat image1, image2, image3;
  image.convertTo(image, CV_32F);
  float sigma = 2.5;
  int num_intervals = 2;
  resize(image, image, Size(0, 0), 2, 2, INTER_LINEAR);
  GaussianBlur(image, image, Size(0, 0), 0.56);
  bool greater_ = true;
  bool smaller_ = false;
  imagevec = createblurimage(image, sigma, num_intervals, 3);
  char imgnumber[1] = {'a'};
  char name_[100];
  for (int octave_ = 0; octave_ < imagevec.size(); octave_++)
  {
    Group_of_images = imagevec.at(octave_);

    for (int size_ = 0; size_ < (Group_of_images.size() - 1); size_++)
    {
      Mat imagecheck1 = Group_of_images.at(size_).clone();
      Mat imagecheck2 = Group_of_images.at(size_ + 1).clone();
      Mat diffimg;
      imagecheck1.convertTo(imagecheck1, CV_32F);
      imagecheck2.convertTo(imagecheck2, CV_32F);
      diffimg = (-imagecheck1 + imagecheck2);
      // strcpy(name_, "window");
      // strcat(name_, imgnumber);
      // // Mat demonstraion;
      // // normalize(diffimg.clone(),demonstraion,0,255,NORM_MINMAX);
      // imshow(name_, diffimg.clone());
      // imgnumber[0] = imgnumber[0] + 1;
      Group_of_diff_images.push_back(diffimg.clone());
    }
    DoGs.push_back(Group_of_diff_images);
    Group_of_images.clear();
    Group_of_diff_images.clear();
  }

  int octave_ = 0;
  for (octave_ = 0; octave_ < DoGs.size(); octave_++)
  {
    Group_of_images = DoGs.at(octave_);
    Image_orientntation = imagevec.at(octave_);
    int i = 1;
    vector<vector<float>> descriptor_values;
    while (i < (Group_of_images.size() - 1))
    {
      cout << "octave" << octave_ << "image_size" << i << endl;
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
                    keypoint.pt = Point(xx_axis * pow(2, octave_), yy_axis * pow(2, octave_));
                    keypoint.octave = octave_ + value * pow(2, 8) + int(round(((value - i) + 0.5) * 255)) * pow(2, 16);
                    keypoint.size = sigma * pow(2, value / num_intervals) * pow(2, octave_ + 1);
                    keypoint.response = abs(D_);
                    float scale = 1.5;
                    float radius_factor = 3;
                    int nbins = 36;
                    Mat histogramcontainer = Mat::zeros(Size(nbins, 1), CV_32F);
                    Mat smoothhistogram = Mat::zeros(Size(nbins, 1), CV_32F);
                    float circularwindowsigma = scale * keypoint.size / pow(2, octave_ + 1);
                    // int radius = int(round(radius_factor * circularwindowsigma));
                    int radius = 7;
                    float weight_factor = -0.5 / pow(circularwindowsigma, 2);
                    float weight;
                    Mat checkimageoreint = Image_orientntation.at(i).clone();
                    // cout << radius << endl;
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
                            // cout << "region_x " << region_x << "  ,region_y  " << region_y << endl;
                            float Gx = (checkimageoreint.clone().at<uchar>(region_y, region_x + 1) - checkimageoreint.clone().at<uchar>(region_y, region_x - 1)) / 255;
                            float Gy = (checkimageoreint.clone().at<uchar>(region_y + 1, region_x) - checkimageoreint.clone().at<uchar>(region_y - 1, region_x)) / 255;
                            float Gvalue = sqrt(pow(Gx, 2) + pow(Gy, 2));
                            float angle = atan2(Gy, Gx) * 180 / pi;
                            if (angle < 0)
                            {
                              angle = 360 + angle;
                            }
                            weight = exp(weight_factor * (p * p + q * q));
                            histogramcontainer.at<float>(0, (int)(angle / 10)) = histogramcontainer.at<float>(0, (int)(angle / 10)) + weight * Gvalue;
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
                    float peak_ratio = 0;
                    keypoint.pt = Point(int(xx_axis * 0.5 * pow(2, octave_)), int(yy_axis * 0.5 * pow(2, octave_)));
                    keypoint.size *= 0.5;
                    keypoint.octave = (keypoint.octave & ~255) | ((keypoint.octave - 1) & 255);

                    for (int scontainer = 0; scontainer < nbins; scontainer++)
                    {
                      int minvalue = (scontainer - 1) < 0 ? (nbins + (scontainer - 1)) : (scontainer - 1);
                      if (smoothhistogram.at<float>(0, scontainer) >= (peak_ratio * max_))
                      {
                        float left_value = smoothhistogram.at<float>(0, minvalue);
                        float right_value = histogramcontainer.at<float>(0, (scontainer + 1) % nbins);
                        int interpolated_peak_index = int((scontainer) + 0.5 * (left_value - right_value) / (left_value - 2 * smoothhistogram.at<float>(0, scontainer) + right_value)) % nbins;
                        float orientation = 360 - (interpolated_peak_index)*360. / nbins;
                        if (abs(orientation - 360.) < 0.0001)
                        {
                          orientation = 0;
                        }
                        KeyPoint newkeypoint = KeyPoint(keypoint.pt, keypoint.size, orientation, keypoint.response, keypoint.octave, keypoint.class_id);
                        keypoints_orientation.push_back(newkeypoint);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      i++;
    }
    Image_orientntation.clear();
    Group_of_images.clear();
  }
  return sortkeypoints(keypoints_orientation);
}