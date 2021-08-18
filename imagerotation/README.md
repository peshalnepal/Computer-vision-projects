# Horizontal and Vetical flip of an image

## Description:

In this project an image is taken and rotated by angle provided by user in both clockwise and anticlockwise direction. Shear rotation is used inorder to rotate the image. Even though output of shear rotation might not be as good as area mapping it is faster and works in image of any channels and any depth.

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **imagerotation** has been created 
- To check the output, Run ***`./imagerotation`*** command in terminal
- If user doesnot pass any angle and direction then image will be rotated 45 degree in anticlockwise direction
- If User wants to pass the angle they wants to rotate the image then they can pass using ***`./imagerotation 90`***</br>Here instead of **90 degree** user can pass any angle form 0 to 360 degree.
- If User wants to rotate angle with specific angle in certain direction then they can do that using following command ***`./imagerotation 90 t`***</br>Here **90** is angle to rotate image and **t** represent the **true** that means rotate image in clockwise direction. If user pass **f** that means **false** and image will rotate in anticlockwise direction.
- After passing all the argument user can also pass image of their own choise to rotate. They need to pass the path to the image using following command ***`./imagerotation 90 t pathtotheimage/imagename.extension`***.
- To close all the window press key **'esc'** from the keyboard

## Input & Output: <br/>
original image <br/>
[original image](photos/check.png)

original image rotated by 45 degree anticlockwise<br/>
[anticlockwise rotated image](photos/anticlockwise.png)

original image rotated by 45 degree clockwise<br/>
[clockwise rotated image](photos/clockwise.png)

## Rotation of an Image:

Image are made up of pixels so while rotation the image we change the pixels coordinate using formula used for rotation of coordinates in 2D plane. i.e.

$`
   \left(\begin{array}{cc} 
  x1\\ 
  y1
  \end{array}\right)=
  \left(\begin{array}{cc} 
  \cos\theta & \sin\theta\\
  -\sin\theta & \cos\theta\\
  \end{array}\right)
  \left(\begin{array}{cc} 
  x\\ 
  y
  \end{array}\right)
  `$

While rotating images using the given formula output coordinates might be in decimal value so while rounding up the value some of the coordinate are not filled in new image or mulpile pixel value gets filled in the same coordinate values. This bring alaising effect where some of the pixel are left empty not carrying any information. There are multiple ways to solve this issue such as:

- **Rotation by Shear:**<br/>
  In this method, instead of roating the image,images are shear to obtain final output. In this method, shearing of the image is perfromed three times, two vertical shear and a horizontal shear. Follwoing matrices in the given order is multiplied to obtain ouput coordinates.<br/>
  $`
   \left(\begin{array}{cc} 
  x1\\ 
  y1
  \end{array}\right)=
  \left(\begin{array}{cc} 
  1 & \tan(\theta/2)\\
  0 & 1\\
  \end{array}\right)
  \left(\begin{array}{cc} 
  1 & 0\\
  -\sin\theta & 1\\
  \end{array}\right)
  \left(\begin{array}{cc} 
  1 & \tan(\theta/2)\\
  0 & 1\\
  \end{array}\right)
  \left(\begin{array}{cc} 
  x\\ 
  y
  \end{array}\right)
  `$

  This method is faster than the method describe above and produce decent result. As in this method as there is used of shearing soo alasing effect doesnot occur as pixel are just slided over to obtain required result. This method works for image of any channel and depth.<br/>
  The problem with this issue even though it is faster is that,
  -  This method does not output quality image. If user pass low res image the output will be worst and unrecognizable. 
  -  This method doesnot work for angles above certain range. Pixels gets jumbled and obtained result can not be used.

- **Rotation by Area Mapping:**<br/>
  In order to produce higher quality image and solve above stated aliasing problems. Rotation by area mapping is used.

  In previous methods destination pixels were determined by rotating the source pixel in give direction by the angle given by user. But In this method instead of determinig destination pixel from source pixel, source pixel which will rotated to given destination pixel is determined. source pixel value which will fill the given destination co-ordinate is determined. Destination pixels are rotated in opposite direction from the direction provided by user in given angle to find the source pixel. If source pixel is obtained then destination pixel is filled with area-weighted average pixel value from neighbours of obtained source pixel .<br/> 
  For each destination pixel, you find the 4 source pixels that it partially covers is used. Compute the destination pixel value as the area-weighted average of those 4 source pixels will give higher quality image. Using this algorithm there does not exist any gap in destination pixel as well as output will be smoothed out. Each source pixels from those 4 pixels is provided with weight. If destination pixel convers larger part of 2nd pixel and small part of other 3 pixels. Then weight of the pixel will be higher than other and has higher influence in destination pixel value. The formula to calculate destination pixel value is

  $`Destination pixel value = (1/N^2) [(N - x)*(N - y)*(f(i,j)) + x*(N - y)*(f(i,j+1)) + y*(N - x)*(f(i+1,j)) +
x*y*(f(i+1,j+1))]`$

  In this formula, N denotes the numbers of subpixels in each pixel, we can just put N=1. (x,y) is coordinate of the destination image in the subpixels.(x,y) is obtained when calculated source pixel is not exact integer. This (x,y) represent number after point in decimal output of the obtained source pixel. f(i,j) denotes the source pixels for respective destination pixel. Four Source pixels are used to determine a single destination pixel value. Weight for each pixel is given and a pixel with more weight effect the destination pixel value. Here terms like **(N - x)*(N - y)** is weight for each pixel. 

  To study more about Rotation by Area Mapping go to the link provided below:
  
  [Rotation By Area Mapping](http://www.idc-online.com/technical_references/pdfs/information_technology/Rotation_and_Fast_rotation_by_Area_Mapping.pdf)

## Steps to follow to rotate image using Rotation by Area Mapping Algorithm:

- At first, the image is read from the path.
- Calculate height and width of the provided image.
- After that height and width of the image are obtained and using the height and width of the output image is also calculated. To calculate that four corners of the image supplied is rotated by given angle using the following formula.<br/>
  $`
   \left(\begin{array}{cc} 
  x1\\ 
  y1
  \end{array}\right)=
  \left(\begin{array}{cc} 
  \cos\theta & \sin\theta\\
  -\sin\theta & \cos\theta\\
  \end{array}\right)
  \left(\begin{array}{cc} 
  x\\ 
  y
  \end{array}\right)
  `$
<br/>obtained (x,y) co-ordinated are compared with each other to obtain max result which will define the final width and height of destiantion image obtained.
- Now after obtaining the final width and height, destination image is created. For each pixel of the destination image, the respective source pixel coordinate is calculated. Here if we want to rotate the image in a clockwise direction, then the anticlockwise formula is used to obtain the source pixel.<br/>
  $`
   \left(\begin{array}{cc} 
  x\\ 
  y
  \end{array}\right)=
  \left(\begin{array}{cc} 
  \cos\theta & -\sin\theta\\
  \sin\theta & \cos\theta\\
  \end{array}\right)
  \left(\begin{array}{cc} 
  x1\\ 
  y1
  \end{array}\right)
  `$
</br>This formula is used to calculate source pixel (x,y) for respective destination pixels (x1,y1). Here we want to rotate the image in an anticlockwise direction so clockwise formula is used. This is done so that the destination pixel can be rotated in clockwise direction to obtain the source pixel. 
- After obtaining source pixel coordinates, the value for the destination pixel is calculated by using Area-average weight  method. The formula to do that is <br/>
$`Destination pixel value = (1/N^2) [(N - x)*(N - y)*(f(i,j)) + x*(N - y)*(f(i,j+1)) + y*(N - x)*(f(i+1,j)) +
x*y*(f(i+1,j+1))]`$

  In this formula, N denotes the numbers of subpixels in each pixel. (x,y) is coordinate of the destination image in the subpixels. f(i,j) denotes the source pixels. Four Source pixels are used to determine a single destination pixel value. Weight for each pixel is given and a pixel with more weight effect the destination pixel value. 
- In this way for every destination pixel value is calculated. Even though this method is time-consuming it produces a promising result  