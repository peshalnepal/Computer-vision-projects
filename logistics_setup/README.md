## Installation of python and jupyter lab
- In order to install python use the following command
  
  `$ sudo apt update`<br/>
  `$ sudo apt install software-properties-common`<br/>
  It is install as it provide better control over packages management

  `$ sudo add-apt-repository ppa:deadsnakes/ppa`<br/>
  Deadsnakes is a Personal Package Archive to manage packages

  `$ sudo apt update`</br>
  `$ sudo apt install python3.8`<br/>
  We can change python version if we want. In this example python verison 3.8 is install

  `$ pip install jupyterlab`<br/>
  `$ export PATH="$HOME/.local/bin:$PATH"`<br/>
  We can use following command to install jupyterlab along with exporting path to use jupyter lab. This will add path locally.

  If this doesnot export path we have to include path in environment file.<br/>
  `sudo -H gedit /etc/environment.`<br/>
  We use this command to open environment file and inside path variable we need to put following path<br/> **`/home/peshal/.local/bin:`**

## Installation of opencv : <br/>
- At first we need to install all the dependencies required to install opencv and run opencv in the machine
  ### following commands to install dependencies
  `$ sudo apt-get update`<br/>
  `$ sudo apt-get upgrade`<br/>
  These commands are used to update and upgrade <br/>

  `$ sudo apt-get install build-essential`<br/>
  `$ sudo apt-get install cmake`<br/>
  `$ sudo apt-get install unzip`<br/>
  `$ sudo apt-get install pkg-config`<br/>
  Build essential contains all packages required to compile files using compilers. </br>
  CMake is tool used to create makefile for building the source code. <br/>
  Unzip is for unzipping purpose. <br/>
  
  `$ sudo apt-get install libjpeg-dev`<br/>
  `$ sudo apt-get install libpng-dev`<br/>
  `$ sudo apt-get install libtiff-dev`<br/>
  These library help to read images and videos locally. These install image tools and video libraries

  `$ sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"`<br/>
  `$ sudo apt update`<br/>
  `$ sudo apt install libjasper1`<br/>
  `$ sudo apt install libjasper1 libjasper-dev`<br/>
  `$ sudo apt-get install libavcodec-dev`<br/>
  `$ sudo apt-get install libavformat-dev`<br/>
  `$ sudo apt-get install ibswscale-dev`<br/>
  `$ sudo apt-get install libv4l-dev`<br/>
  `$ sudo apt-get install libxvidcore-dev`<br/>
  `$ sudo apt-get install libx264-dev`<br/>
  `$ sudo apt-get install libgtk-3-dev`<br/>
  These also help read images and videos.

  `$ sudo apt-get install libatlas-base-dev`<br/>
  `$ sudo apt-get install gfortran`<br/>
  These install optimization library to be used for opencv

  `$ git clone https://github.com/opencv/opencv`<br/>
  `$ git clone https://github.com/opencv/opencv_contrib`<br/>
  These help in download opencv and free modules for opencv from the git


    `$ cd ~/opencv`<br/>
    `$ mkdir build`<br/>
    `$ cd build`<br/>
    `$ cmake -D CMAKE_BUILD_TYPE=RELEASE \`<br/>
            `-D CMAKE_INSTALL_PREFIX=/usr/local \`<br/>
            `-D WITH_CUDA=OFF \`<br/>
            `-D INSTALL_PYTHON_EXAMPLES=ON \`<br/>
            `-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \`<br/>
            `-D OPENCV_ENABLE_NONFREE=ON \`<br/>
            `-D BUILD_EXAMPLES=ON ..`<br/>
  Create build directory inside opencv directory that we jsut clone . After that build into the build directory using provided cmake

  `$ make -j4`<br/>
  `$ make install`<br/>
  Here the opencv is build and install using the given command. Here **-j4** helps speed up the process , 4 means no of core provided in your cpu.<br/>

  To check whether opencv is correctly install or not just open jupyter lab and type `import cv2` and run. It will run without an issue if opencv is install properly

<br/>

## OpenCV Modules
- ### ***Core module:***
  This is the main module which is implemented in other modules of Opencv. This module defines how image is stored as image is not just an regular value which fits into any of the data type. Images needs to be store in Matrix format as well as how data is store in the matrix also have great influenece in the images. Image are store in matrix so to store image we use object of class `Mat`. This module defines how images are store, scan. This modules provides function for mathmatical calculation with pixels of images.

- ### ***imgproc module:***
  This module is responsible for processing the images. It contains function for blending two images, thresholding images i.e. if pixel value which cross the given threshold will be processed accordingly , bluring and smoothing the images as blur images is needed for some ttask in which higher details of images is not required. Histogram of an images which tells which color are highly present in the picture. It also contain fucntion to calculate gradient of an images. 

- ### ***highgui module:***
  As images cannot be seen directly in the window provided by the IDE so we need window where images as well as video can be displayed . This module contains all the files and syntax which can be used in displaying images and videos along with other graphical interface so that we can work with image

- ### ***imgcodecs module:***
  Images have different file format so inorder to read these images we need function such as `imread()` which is inside this module which read images and stores them in matrix variable. We can read image of any shape, any depth , convert image into grayscale while reading images. To store image also we need `imwrite()` function where we need to pass proper image location with extension.
  <br/>