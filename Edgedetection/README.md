## TO RUN PROJECT IN YOUR TERMINAL
- Download the code from the Git
- Run ***`sudo apt-get install cmake`*** command
- If Opencv is not installed in your device install open cv library
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **edgedetect** has been created 
- To check the output, Run ***`./edgedetect`*** command in terminal
- If user want to apply edge detection to specific image the path to the image with image of image should be pass in ***`./edgedetect pathtotheimage/imagename.extension`*** 
- To close all the window press key **'esc'** from the keyboard
  
### OUTPUT:
Original Image:<br/>
**[Original Image](photos/check.png)**<br/>

Detected edge of image after applying sobel filter</br>
**[Edge detection](photos/edge_detect.png)**<br/>


## Edge Detection 
<p>Edge are region in the images where there is sharp change in pixel intensity. We apply matrix which is smaller in size of the actual images. The process of apply the martix which is also called filter or kernal to the image is convolution.</p>
<p>Convolution is simple multiplication method where matrix of different size but of same dimensionality are multiplied with each other to produce output image of same dimesionality.Comvolution methods are quite used for image processing like bluring, smoothing, edge detection e.t.c.</p>
<p> When edge changes then their will be directional change in intensity of color in images. Kernel for edge detection when applied to the image then they will produce an final image highlighting edges of the images. There are vertical edge detector and horizontal edge detector with have their own type of kernel for edge detection. Output of the both vertical and horizontal edge will gives total edge of an image.</p>


| | | | | | | | |
| - | - | - | - | - | - | - | - |
| 100 | 100 | 100| 100| 0 | 0 | 0| 0|
| 100 | 100 | 100| 100| 0 | 0 | 0| 0|
| 100 | 100 | 100| 100| 0 | 0 | 0| 0|
| 100 | 100 | 100| 100| 0 | 0 | 0| 0|

Let us suppose, an image of size m * n where m is no of rows and n is no of columns in this example we are supposing 4 * 8 image.We can see vertical edge as there is change in pixel valuemoving from left to right.

| | | | 
| - | - | - | 
| 1 | 0 | -1| 
| 1 | 0 | -1| 
| 1 | 0 | -1| 


This is 3*3 vertical edge detector . The output image will be of size<br/>
**m-f+1 * n-g+1**<br/>
where m can be number of rows in input image, f be number of rows in the filter, similar n can be number of columns in input image, g be number of columns in the filter.

output of this example will be of size 2*6:

| | | | | | |
| - | - | - | - | - | - |
| 0 | 0 | 300| 300| 0 | 0 | 
| 0 | 0 | 300| 300| 0 | 0 |


In similar way we can apply horizontal edge detection and when combining both output we can obtain total edge for the image.

In order to know more about convolution , we can follow the link provided.<br/>
[About Convolution](https://homepages.inf.ed.ac.uk/rbf/HIPR2/convolve.htm)

There are many different edge detection some of them are:<br/>
- **Prewitt Edge Detection:**<br/>
  To calculate magnitude and orientation of edge prewitt edge detection is correct and computationally fast. It consists of two kernel for horizontal edge detection and vertical edge detection and sum of all terms in the kernel is zero. Here +-1 and 0 is used for creating kernel and one property of derivative mask state that more weight , more edge detection so even though this edge detector is comupationally fast, output is quite noisy.
  
- **Sobel Edge Detection:**<br/>
  Sobel edge detection detect the edges of an images by mearing rate of change of pixel intensity with respect to position of pixel in and image and emphaysize pixel high higher intensity change. Sobel edge detector identify either vertical or horizontal edge. kernel used for horizontal and vertical edge detection are matrix that are rotated by 90 degree from each other.

- **Kirsch Edge detection:**<br/>
  In kirsch Edge detection kernal of odd number of qows and colums are used and rotate in eight main compass directions. Magnitude and direction of each detected edges is determine by kernel which produces maximum value for given pixel.

- **Robinson Edge detection:**</br>
  This edge detection is similar to that of kirsch edge detection but kernel are symettrical to their directional axis so we need to find pixels value of just 4 kernels to determine edge and output of remaining 4 kernels can be found automatically. It is computationally fast as just 3 numbers 0, 1 and 2 are used in this .

- **Laplacian of Gaussian edge detection:**<br/>
  Until know we have seen kernels which perfome first derivative in the image , but in Laplacian of Gaussian  edge detection second order derivative mask is used. It has two effect it smoothes image and determine edge .The Laplacian is generally used to found whether a pixel is on the dark or light side of an edge.
  
- **Canny Edge Detection:** <br/>
  Canny edge detector uses sobel operator and makes it better by removing unwanted edges. After calculating gradient and orientation using sobel operator, We perform canny operation. We thin out the edges to one pixel wide and perform hysteresis thresholding which consist of two thresholds. The edge which passes hysteresis thresholding are kept and otherwise removed.

To study more about this topic follow the link provided:<br/>
[About edge detectors](https://www.tutorialspoint.com/dip/)<br/>
[More about edge detectors](https://airccse.org/journal/jcsit/1211csit20.pdf)

In this task we have used sobel edge detection as it is one of the most common type of edge detector. <br/>
### Following syntax are used for determining edges using sobel operator <br/>

`GaussianBlur(source_image,destination_image,Size,sigmax,sigmay);`<br/>
Before performing edge detection we need to perform bluring and smoothing out of an image so that we can determine edges and ignore noises. We use gaussian blur for that purpose.

`Sobel(source_image,destination_image,depth,x_order,y_order,kernel_size,scale,delta,BORDER_CONSTANT);`<br/>
This is the syntax used in to find edge of an image using sobel operator. Here, we need to pass input images and output which store the detected edges. `depth` determine depth of an output which might not be as same as input image. so depth of output image won't match with input image as it varies during calculation. so we generally consider depth more than 8 unit and pixel of ouput can carry singned character i.e. in depth we put `CV_16S`. `x_order` and `y_order` determine whether to find vertical or horizontal edge. To determine vertical edge we consider x_order as 1 and y_order as 0. If we put x_order 0 and y_order 1 we obtain horizontal edge. kernel size must be odd no and choose as required. `scale` and `delta` is consider to be 1 and 0. 

`convertScaleAbs(source_image, destination_image);`<br/>
This is responsible for converting 16bit signed image to 8bit unsigned image

`addWeighted(source_image1,alpha,source_image2,beta,gaama,finalimage);`<br/>
Here two images are blend together to obtain final result. Here alpha and beta gives blending ratio and gamma determine brightness of final image

To study more about cobel operator in opencv follow the given link:<br/>
[sobel operator in opencv](https://docs.opencv.org/4.5.2/d5/dc4/tutorial_adding_images.html)
<br/>