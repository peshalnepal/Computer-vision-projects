## TO RUN PROJECT IN YOUR TERMINAL
- Download the code from the Git
- Run ***`sudo apt-get install cmake`*** command
- If Opencv is not installed in your device install open cv library
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **hello** has been created 
- To check the output, Run ***`./hello`*** command in terminal
## Import images and videos

### For Images
Images are read from the computer using <br/>
`Mat img = imread(path to the image,flags);` <br/>
Here in 'path to image' actual path to the image you want to read needs to be provided. In flags there are couple of flags which user can set on how to read an image. Usually **`IMREAD_COLOR`** flag is used as this loads the image and store it in Matrix format. **`IMREAD_GRAYSCALE`** flag loads image as grayscale image. 
The image is read in matrix format with matrix rows representing height of an image and column representing width.<br/>
Read image is displayed in an window using following code:<br/>
`imshow("Display window", img);`<br/>
Here **Display window** is title of the window where image is shown and **img** is what to be displayed in the window.<br/>
These display window sometimes throws an error when tried to close by clicking close icon so inorder to close window we need to use `waitkey()` along with button which when pressed will close the window.<br/>
`waitkey(time in milliseconds)` <br/>
waits until provided time before user can close the window <br/>


### For Videos
Videos are read by with help of VideoCapture class<br/>
`VideoCapture cap;`<br/>
`cap.open(path to video file)`<br/>
or<br/>
`cap.open(device ID)`<br/>
cap is object of VideoCapture class it either reads images from video file in the given path or from actual camera whose ID user has provided in device ID. If 0 is passed it will read data from primary camera of your device.<br/>
**`cap.read()`** function is used to read each frame of the provided video and store in one of the matrix so its complete syntax will be <br/>
`Mat img;`<br/>
`cap.read(img);`<br/>
As videos is simply images arranged in sequence so all this needs to be kept on infinite loop so that **`cap.read()`** can read most of the frames from the video and display it . Otherwise it will be still image



## Basic of Image Processing

### Color Mappings<br/>
There are various color spaces. Out of which RGB,HLS,HSV are quite popular ones.
These color spaces define how pixel is represented. In RGB color space, intensity value of Red, Green and Blue is responsible for defining color of a pixel.Similarly for HSV, Hue define primary color of pixel, Saturation define intetnsity of color and Value define lightness or darkness of color in the pixel.<br/>
In order to change the convert image from one color space to another we use following script<br/>
`cvtColor(source image,destination image,code,dstCn)`<br/>
In **`code`** which is int value we define from which color space to which we want to change for example if we want to change from BGR to HSV we can simpy put the code **`COLOR_BGR2HSV`**<br/>

### Threshold<br/>
In this, if the pixel value is greater than threshold value then one of the thresholding type is to be applied.<br/>
'threshold(source image, destination image , threshold value, max value, type)`<br/>
There are 5 types of thresholding <br/>
- **Threshold Binary :** If pixel value is greater than threshold then assign those max value and pixel whose value is smaller than threshold assign it to zero.
- **Threshold Binary, Inverted :** It is inverse of Threshold Binary.
- **Truncate:** If pixel value is greater than threshold then assign those threshold value to the pixel and whose value is smaller than threshold leave pixel as it is.
- **Threshold to Zero :** If pixel value is greater than threshold then leave pixel as it is and pixel whose value is smaller than threshold assign it to zero.
- **Threshold to Zero, Inverted :** It is inverse of Threshold to Zero.

### Bluring and Smoothing<br/>
Some time while during image processing it is unecessary to provide every detail of an image. If every detail of the image is provided then it might acts as noise . So we need to blur and smooth out the image.<br/>
In order to blur the image we use kernel.**Kernel** is simply matrix smaller than your original image. Inside the kernel there is numerical value and kernal must be square matrSix with odd numbers of sides.Kernel change value of pixel by combining it with different amount of neighbouring pixels. It is applied to each and every pixels one by one to produce final pixel.[More about kernels](https://github.com/atduskgreg/opencv-processing-book/blob/master/book/filters/blur.md)<br/>
- ***Gaussian Blur***<br/> In gausian blur , we use normal distribution central pixel has higher weight in the given kernal and further we deviate from the central pixel in the kernal value decreases. It is determine by the standard deviation. Higher deviation, value of other pixel will be close enough to the central pixel and smaller the deviation lesser the value.

## Cmake
Cmake is tool used for building of projects. It helps create MakeFile for the respective project including all the necessary library and directories , so that end user can easily build and run the project. We need to create **CMakeLists.txt** file where we define all necessary packages, software version for given project, all the directories required to run the project. After creating the following .txt files and including all required syntax we use following commands lines.
### Commands:
- `cmake -S . -B .`<br/>
  Here after **`-S`** there is **`.`** this means that main source file is in the same diectory where the .txt files resides. If it lie in any other location we need to remove **`.`** and specify our source file path<br/>
  Here after **`-B`** there is **`.`** this means makefile is created in same place where the .txt files resides. If we want to build our makefile some where else we specify the path over here<br/>

- `make`<br/>
  After Makefile is created, we can use this command to make executable file for out project and after that we can run our executable file 

### Syntax to be used in .txt file:

- `cmake_minimum_required(VERSION 3.10)`<br/>
  This syntax define that minimum 3.10 version of cmake is to be install in order to build this project.

- `set(CMAKE_CXX_STANDARD 17)`<br/>
  `set(CMAKE_CXX_STANDARD_REQUIRED ON)`<br/>
  If we want specific C++ standard so that some additional features can be added to our project we specify over here. Here c++ Standard of 17 is used it means below 17 if user wants to build this project it won't get build and it is required.

- `project(hello VERSION 1.0)`<br/>
  `add_executable(hello main.cpp)`<br/>
  Here project version is define and we need to update this with every new updates. **hello** is the project name as well as name of executable that produce after building the given project. In second syntax, executable hello is linked with main source file i.e. ***main.cpp*** , so when **main.cpp** file get build the executable will be **hello**

- `find_package(OpenCV REQUIRED)`<br/>
  As this project is based on opencv so with OpenCV packages it will not get build. If there is any package that is in your device and necessary to your project, we can use this syntax to find the package.

- `include_directories(${OpenCV_INCLUDE_DIRS})`<br/>
  `include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)`<br/>
  This syntax can be use if we want to incude directories containing header files and all other required files. As for this project, we need opencv directories so we have included **`${OpenCV_INCLUDE_DIRS}`** which provide location to directories of opencv. If our source file contains header file then we need to include the directory where the custom header files resides as shown in second example.

- `add_subdirectory(include)`<br/>
  This syntax is used if we want to look for files required for the project in some directories. we need to add in this way.

- `target_link_libraries(hello ${OpenCV_LIBS})`<br/>
  `target_link_libraries(hello PUBLIC ${PROJECT_SOURCE_DIR}/lib/customlibraryfile.cpp)`<br/>
  This syntax is used to link library to our source code as it will be required to execute the final output. Here in first example we have given link to opencv libraries by using **`${OpenCV_LIBS}`** . Similary if there are other library we can link in same way. <br/>
  
  For this **`${OpenCV_LIBS}`** we need to create folder name **opencv2** inside **/usr/local/lib** and copy all the opencv library files inside this folder from the location **/usr/local/lib** as everyfiles start with **libopencv**<br/>

  If we want to link our own custom library files we need to create lib folder inside our project directory and include all custom library files. Then we can link this library files by providing their location and name as shown in second example.<br/>
  Here `${PROJECT_SOURCE_DIR}/lib/customlibraryfile.cpp` is library file we want to link with our project so project name **hello** is being supplied


Here is link to the documentation of CMake for more syntax and information about CMake<br/> [Cmake documentation](https://cmake.org/cmake/help/v3.21/index.html)
