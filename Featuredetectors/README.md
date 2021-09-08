# Apply SIFT,SURF and ORB feature detector algorithm.
In this project Feature Detection algorithm is applied to the image specially the feature detect algorithm mentioned in the title.

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **featuredetect** has been created 
- To check the output, Run ***`./featuredetect`*** command in terminal
- If user want to apply feature detect algorithm in specific images, the path to the images with their name and extension of images should be pass in ***`./featuredetect pathtotheimage/imagename.extension pathtotheimage/imagename.extension`*** . Two images are to be passed as feature are to be compared.
- To close all the window press key **'esc'** from the keyboard

## Input & Output: <br/>
original images<br/>
[original image ](photos/picture.png)

[original image 1 ](photos/picture2.png)

Keypoints on the supplied images using SIFT algorithm<br/>
[Keypoints on the image](photos/output_.png)

[Keypoints on the image 1](photos/output_1.png)

Feature Descriptor output to match features <br/>
[Descriptor output ](photos/output_descriptor.png)