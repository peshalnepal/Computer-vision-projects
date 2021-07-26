## TO RUN PROJECT IN YOUR TERMINAL
- Download the code from the Git
- Run ***`sudo apt-get install cmake`*** command
- If Opencv is not installed in your device install open cv library
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **histogram** has been created 
- To check the output, Run ***`./histogram`*** command in terminal
- To close the windows press key **'s'** from the keyboard
  
### OUTPUT:
***About Image :***<br/>
[About image](photos/Aboutimage.png)

In this image, image size with their dimesnion and no of pixels is shown. Pixel values with max pixels in all the channels is shown in this image for both grayscale and rgb image.


***Colorful Image :***<br/>
[colorful demo image](photos/demo.png)

***Histogram of the image:***<br/>
[Historgam of colorful image](photos/histogram_for_rgb_image.png)

In this histogram we can see that there are large no of white pixels as we can see spikes of all three color channel at right hand side of the image which represent higher pixel value. We can see large spikes at lower pixel value in blue channel that means there are large no of pixel in blue channel with lower pixel value similar for other channels.

***Grayscale Image :***<br/>
[grayscale demo image](photos/grayscale_image.png)

***Histogram of the image :***<br/>
[Historgam of grayscale image](photos/histogram_for_grayscale_image.png)

In this histogram we can see that there are large no of white pixels as we can see spikes at right hand side of graph which represent higher pixel value at single channel. We can see spikes at lower pixel lever which represent presence of darker color. 

## Color Channel
As Images are simply set of pixel which provide visual representation. In each pixel, there will be real number and these number in all the pixel together form a matrix. So, we can say that images are large matrix which visually represent something . Each pixels can be represented by 8bit or 10bit value. This define depth of the pixel. Higher bits to represent single pixel more shades will be present to represent color. For examples, 1 bit pixel value can only represent grayscale image with black and white color but 8 bit pixel value can represent grayscale image with 256 different shades of gray. <br/>
Images can be grayscale images or Color images. Grayscale image differ from color images by the color channels. In grayscale images there is single color channel so single set of rows and colums can represent Grayscale image. In Color images, there are three channels which differ based on color space. For images represend by RGB color space, there are 3 channels Red, Blue and Green. Each channel consist of set of rows and columns and combining the pixel value from all the 3 channels will get final colorful pixel output. For images represent by HSV color space , 1st channel represent hue of pixel , 2nd channel represent Saturation of pixel and final channel represent value of pixel. For images represent by HLS color space , 1st channel represent hue of the pixel , 2nd channel represent lightness of the pixel and final channel represent saturation of the pixel. <br/>

## Histogram
Histogram is visual representation where data collected are organised in sets of predefined bins. Data are not just intensity values it can be any values which help define an image. As for any image with 8 bit pixel depth, value of pixels lie in between 0 and 255. So total no of bins so that all pixels lie in one of bin is 256 bins. If we plot histogram of an image then along horizontal axis there lie pixel values form 0 to 255 and along vertical axis lies frequency , if single pixel value appear multiple times in image then its frequency will be high. For grayscale image, histogram of single channel will be enough be used to analyse the image. For Color image, histogram of all three channels will be required to analyse the image.<br/>
### Histogram of image can be obtain using following syntax:
- `calHist(const Mat* images,int nimages,const int* channels,InputArray mask,SparseMat& hist,int dims,const int* histSize,const float** ranges,bool uniform,bool accumulate);`<br/>
  Here ,<br/>
  `const Mat* images` : Source arrays with same depth and same size<br/>
  `int nimages` : no of source images<br/>
  `const int* channels` : list of dims channels used to compute histogram. Here 0 means histogram of intensity of first channel is calculated, 1 means histogram of second channel is calculated and 2 means histogram of third channel is calculated<br/>
  `InputArray mask` : If we want histogram of specific part of image we provide mask and <br/>
  `SparseMat& hist` : Mat object where histogram will be store<br/>
  `int dims` : Histogram dimensionality that must be positive <br/>
  `const int* histSize` : total no of bins per dimension (channels)<br/>
  `const float** ranges` : rnage of value to be measured <br/>
  `bool uniform` : The bin sizes are the same if it is set to **True**<br/>
  `bool accumulate` : The histogram is cleared at the beginning if it is set to **False**<br/>

  ***For example :***<br/>

  `calcHist(&imRGB[0],1,0,Mat(),blue_hist,1,&histSize,histrange,true,false);`
  
  Here in this example, we are passing imgRGB as inputarray source. These are `Mat` Vector which store color channels after they are splitted from the original image. Out of three channel we are passing 1st channel i.e. blue channel as our input.We are passsing single image channel of an image as input, soo value in `int nimages` will be **1** and `const int* channels` will be **0** as matrix that we have passed only consist of one dimension. We are not using any mask so we have passed empty matrix function i.e. `Mat()` . Output is store in `blue_hist`. 

  Obtained Mat image i.e. `blue_hist` is at first normalized as large no of pixels may have similar pixel value and ploted in another Image create using `Mat()`<br/>
  **following are the syntax used to do the task :**<br/>
  `int width=512;`<br/>
  `int height=428;`<br/>
  `int container=cvRound(width/histSize);`<br/>
  `Mat histrgbimage(height,width,CV_8UC3,Scalar(255,255,255));`<br/>
  `normalize(blue_hist, blue_hist, 0, histgrayimage.rows, NORM_MINMAX, -1, Mat() );`<br/>
  
  `width` and `height` determine width and height of an image in which histogram is plotted. `container` define size of bin in which pixel whose value resemble with value inside bin are stored.<br/>
  `normalize` function in used for normalizing histogram as the value in histogram can vary a lot and can be really high which will be impossible to fit inside an image of smaller size so histgram is normalize between 0 and height of the image in which we show the histogram.

  
