# Apply AffineTRansformation

## Description
In this project Affine transformation is applied in the image supplied by user. Translation, Rotation and shearing is applied in the provided image from scratch. 

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **affinetransform** has been created 
- To check the output, Run ***`./affinetransform`*** command in terminal
- If user want to apply affine transormation in specific image, the path to the image with name and extension of image should be pass in ***`./affinetransform pathtotheimage/imagename.extension`*** 
- To close all the window press key **'esc'** from the keyboard

## Input & Output: <br/>
original image <br/>
[original image](photos/check.png)

Image rotated by 100 degree in clockwise direction and translated by 100 pixels in both x and y plane<br/>
[rotated and translated image](photos/translationandrotation.png)

Image sheared along x_plane<br/>
[sheared image](photos/sheared.png)

## Affine Transformation

Affine transformation is a transformation in which after transformation colinearity is preserved among the coordinates. Two points that lie in the same straight line will lie in a straight line after transformation. 

In linear transformation, Each vertex is considered as a vector and apply a transformation matrix to it via matrix multiplication. Linear transformation changes the shape of the object considering origin as the center.

$`
\left(\begin{array}{cc} 
x1 \\ 
y1
\end{array}\right)=
\left(\begin{array}{cc} 
1 & 0\\
0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y
\end{array}\right)
`$ 

This is linear translation here the matrix vertex (x,y) is translated using the identity matrix to (x1,y1).
The output will be (x,y) as the identity matrix is being used. By changing the value inside those **2*2** matrix we can rotate, transform the shape of the object whose vertices we supply. 

The affine transformation adds one additional ability i.e. it helps translate the object away from the origin.

$`
\left(\begin{array}{cc} 
x1 \\ 
y1
\end{array}\right)=
\left(\begin{array}{cc} 
1 & 0\\
0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y
\end{array}\right)+
\left(\begin{array}{cc} 
0\\
0
\end{array}\right)
`$ 
 
Here we are translating the vertices by (0,0). If we want to translate it by more value we can change that. 

There is a more elegant way to apply affine transform instead of multiplying and add. We can change the **2\*2 matrices** used for multiplication to **3\*3 matrices** 

$`
\left(\begin{array}{cc} 
x1 \\ 
y1 \\
1
\end{array}\right)=
\left(\begin{array}{cc} 
a & b & c\\
d & e & f\\
0 & 0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y\\
1
\end{array}\right)
`$ 

Hereby changing values of a,b,c,d,e, and f we can change the input vertices. As matrix multiplication of 3*3 matrices and 2*1 matrix is not possible so the input coordinate matrix is changed by adding one at last. 

### Scaling:
If the user wants to change the width and height of the object user can change just simply change the value of a and e in the matrix. By changing **a** the width of the object increases where as changing **e** increases the height. 

The matrix used for scaling the image :

$`
\left(\begin{array}{cc} 
x1 \\ 
y1 \\
1
\end{array}\right)=
\left(\begin{array}{cc} 
a & 0 & 0\\
0 & e & 0\\
0 & 0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y\\
1
\end{array}\right)
`$ 

### Shearing:
If the User wants to shear the object along the x-axis value inside **b** is changed and if the user wants to shear the object vertically value of **d** is to be changed. 

The matrix used for shearing the image :

$`
\left(\begin{array}{cc} 
x1 \\ 
y1 \\
1
\end{array}\right)=
\left(\begin{array}{cc} 
1 & b & 0\\
d & 1 & 0\\
0 & 0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y\\
1
\end{array}\right)
`$ 

### Translation: 
In order to translate the object the value in **c** and **f** is to be changed.

The matrix used for translating the image:

$`
\left(\begin{array}{cc} 
x1 \\ 
y1 \\
1
\end{array}\right)=
\left(\begin{array}{cc} 
1 & 0 & c\\
0 & 1 & f\\
0 & 0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y\\
1
\end{array}\right)
`$ 

### Rotation:
In order to rotate an object there involves multiple steps. 
- At first, the object is to be shear in a horizontal direction i.e. changing the value in **b**
- Then shearing object along horizontal direction i.e changing the value in **d**
- Object gets rotated but scaling does not match the original object so it needs to be tweaked.

Rotation matrix i.e. commonly used to rotate the image by a given angle is

$`
\left(\begin{array}{cc} 
x1 \\ 
y1 \\
1
\end{array}\right)=
\left(\begin{array}{cc} 
\cos(\theta) & -\sin(\theta) & 0\\
\sin(\theta) & \cos(\theta) & 0\\
0 & 0 & 1
\end{array}\right)
\left(\begin{array}{cc} 
x\\ 
y\\
1
\end{array}\right)
`$