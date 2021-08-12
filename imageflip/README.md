# Horizontal and Vetical flip of an image

## Description:

In this project an image is taken and horizontal and vertical flip is applied to the image along with its grayscale form.

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **flipimage** has been created 
- To check the output, Run ***`./flipimage`*** command in terminal
- If user want to flip specific image, the path to the image with name and extension of image should be pass in ***`./flipimage pathtotheimage/imagename.extension`*** 
- To close all the window press key **'esc'** from the keyboard

## Input & Output: <br/>
original image <br/>
[original image](photos/image.png)

original image flip across horizontal axis <br/>
[horizontally flipped image](photos/color_horizontalflip.png)

original image flip across vertical axis <br/>
[vertically flipped image](photos/color_verticalflip.png)

grayscale image flip across horizontal axis  <br/>
[horizontally flipped grayscale image](photos/grayscale_horizontalflip.png)

grayscale image flip across verical axis <br/>
[vertically flipped grayscale image](photos/grayscale_verticalflip.png)


## About Images:
Images are the captured by cameras and displayed in displaying device. The image that we view are stored in matric with height and width of pixel represented by rows and columns of the matrix. In opencv images are read and store in Mat obj. It consist of two part header which contains information about how matrix is store, size, address where matrix of an image is being stored and pointer pointing to the location where matrix is stored. When copying of matrix occur the header will be different for each object but the pointer of both matrix will point to the same address where matrix of image is being stored. So when we change copied image it will bring change in original image. 
### Syntax to read and store image:
`Mat mat=imread(path,code);`<br/>
In path we define path where image is stored and in code we provide way to read an image. If image is being read 


While performing image procesing we somtimes need to excess pixels at specific location so in order to excess each pixel value we use following syntax
### Syntax to read each pixels of an grayscale image
`imgae.at<uchar>(i,j)`<br/>
we are reading pixels at location i,j where i represent row value and j represent column value from gray scale image that is a reason we are using `uchar` inside `<>` cause each pixel contains 8 bit value considering depth of pixel is 8 bit for grayscale image.

### Syntax to read each pixels of an color image
`imgae.at<Vec3b>(i,j)`<br/>
we are reading pixels at location i,j where i represent row value and j represent column value from color image that is a reason we are using `Vec3b` inside `<>` cause there are 3 channel and each pixel from eacn channel contains 1 byte value in them considering depth of pixel is 8 bit.



## Horizontal flip in image with example and explanation:

`Mat img=imread("photos/image.png",IMREAD_COLOR);`<br/>
`Mat dimg=img.colne();`<br/>
`for(int i=0;i<img.rows;i++)`<br/>
`{`<br/>
    `for(int i=0;i<img.rows;i++)`<br/>
    `{`<br/>
        `dimg.at<Vec3b>(i,j)=img.at<Vec3b>((img.rows-1)-i,j);`<br/>
    `}`<br/>
`}`<br/>


`Mat img=imread("photos/image.png",IMREAD_COLOR);`</br>
Using this syntax image for the given path is read in Color version i.e img contains pixel with 8 bit depth and 3 channels

`Mat dimg=img.colne();`<br/>
Using this syntax img is clone to dimg so that property of dimg matches that with img we have just read. IF we simply equals img with dimg for example `Mat dimg=img` then header will be different for both the Mat object but their pointer will point to same pixel matrix at same location. so when changing one value of other will also change. To avoid that clonning is done so that different object will point to same pixel matrix but at different so changing one will not affect other.

`for(int i=0;i<img.rows;i++)`<br/>
`{`<br/>
    `for(int i=0;i<img.rows;i++)`<br/>
    `{`<br/>
    `}`<br/>
`}`<br/>
using this for loop , the value of i and j will change with respect to numbers of rows and columns in the given image.

`dimg.at<Vec3b>(i,j)=img.at<Vec3b>((img.rows-1)-i,j);`<br/>
We are reading pixels form the images with three channels with pixel depth of 8 bit so the ouptput will be `Vec3b`. For the horizontal flip the image in the top row must be at the buttom and pixels at the buttom needs to be at top of the images, so goes for all other pixels and that is what we are doing by subtracting i from total rows of the image i.e `(img.rows-1)-i`
<br/>