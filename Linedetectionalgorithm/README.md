# Line detection algortihm 

## Description:

In this project, Video is caputured or read from the path provided and mask lines present in the videos using line detection algorithm.

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **linedetect** has been created 
- To check the output, Run ***`./linedetect`*** command in terminal
- If User want to capture image from secondary camera source such as camera attached through USB then ***`./linedetect c 2`*** command is to be used. Here **c** represent camera and 2 represent index of camera. If we place 0 instead of 2 it represent default camera of your device.
- If User want to detect lines in the videos then following command needs to be executed
***`./linedetect v path`*** where v represent video and in path we provide path along with name of video with its' extension.
- To close all the window press key **'esc'** from the keyboard

## Final Output: <br/>
Output of a image after applying Hough Transform<br/>
[Output Image](photos/outputimage.png)

Ouput Video after applying Hough transform<br/>
[Final Video](https://drive.google.com/file/d/1-nxUmn9jB2p7CNxmzfa0-1HMMazNyZxC/view?usp=sharing)

## Line detection by using Hough Transform :
<p>Line detection algorithm identify straight lines that exist in image. Line detection algorithm uses Hough transform which is feature extraction algorithm . After detection of the edge, if edge represent straight lines then we use this algorithm to highlight the straight line that exist in the image. There are multiple steps to be followed inorder to apply this algorithm and detection straight lines.</p>

### Steps 
- Read Image or Video from the source and store them in matrix form.
- Apply algorithm for blurring and smoothing out the image. In this project gaussian blur is being used. 
- Edge detection algorithm is applied after blurring and smoothing an image. Canny Edge detection is suitable for this job as it highlights the important edges and discards the noise.
- Output from edge detection is passed to the funtion that implement Hough transform. Output of Hough tranformation will be an image in which detected straight linee is highlighted.

## Hough Transform
Hough Transform is one of the popular algorithm used for line detection algorithm. It is used for feature extraction from the images. In Hought Transform , we use equation $`r = x\cos\theta + y\sin\theta`$ to represent a straight line rather than $`y = mx + c `$ cause for vertical line value of m goes to infinity. 

In **$`r = x\cos\theta + y\sin\theta`$** equation, where 
`r` is the distance from the origin to the closest point on the straight line, and $`\theta`$ is the angle between the x axis and the line connecting the origin with that closest point.

## Steps in Hough Transform:
- Input for the Hough transform is the matrix from the edge detection algorithm. Only the pixel with a value above the threshold value is considered.
- As for all the pixels above the threshold value, possible values of `r` and $`\theta`$ of lines that passed through that pixel is calculated and stored in matrix whose column represent value of $`\theta`$ and rows represent distance from origin to the closet point in straight line i.e.`r` . Max value to $`\theta`$ goes up to $`360\degree`$ and Max value of `r` goes up to the sum of total numbers of rows and columns for the image. For each pixel value of `r` is calculated for all $`\theta`$ from 0 to 360 and stored. The formula to caluclate value of `r` using $`\theta`$ and $`x`$ $`y`$ of pixel is<br/>
 $`r = x\cos\theta + y\sin\theta`$
- A matrix is obtained from above process. If two pixels or more than two pixels lie on same straight line, then one of the values of `r` and $`\theta`$ calculated for those pixels will be same. Max value above threshold level is viewed from the above matrix and their respective `r` and $`\theta`$  value is used to create straight line.
- To calculate straight line in the image, `r` and $`\theta`$ filtered from above process are used. 
  - At first y is calculated when x is 0.The resultant coordinate will be in the form (0,y). If obtained y is smaller than 0 or more than rows of the image.  Then Instead of calculating y , x is calcuated. If y is less than zero, then x is calculated considering y equals to zero for the given image. The resultant coordinate will be of  similar to (x,0).  If y is more than number of rows, then x is calculated considering y to number of rows for the given image. The resultant coordinate will be of similar to (x, rows).
  - To find the second coordinate, y is calculated when x is max which equals to number of columns in the image. The resultant coordinate will be in the form (columns,y).If obtained y is smaller than 0 or more than rows of the image. Then Instead of calculating y, x is calculated when y is zero if y is smaller than zero. The resultant coordinate will be of similar to (x,0). If y is greater than no of columns in the image, x is calculated considering the value of y to be number of columns of the image. The resultant coordinate will be in the form (x, rows).
- In this way, two of the coordinates can be obtained to calculate the straight line. Straight line is plotted with `line()` function in OPENCV using those two coordinates in the image.

 
To Read more about line detection algorithm:<br/>
[Hough Transform ](https://homepages.inf.ed.ac.uk/rbf/HIPR2/hough.htm)<br/>
[Hough Transform Video explanation](https://www.youtube.com/watch?v=XRBc_xkZREg)