**Import images and videos**

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



**Basic of Image Processing**

_Color Mappings_<br/>
There are various color spaces. Out of which RGB,HLS,HSV are quite popular ones.
These color spaces define how pixel is represented. In RGB color space, intensity value of Red, Green and Blue is responsible for defining color of a pixel.Similarly for HSV, Hue define primary color of pixel, Saturation define intetnsity of color and Value define lightness or darkness of color in the pixel.<br/>
In order to change the convert image from one color space to another we use following script<br/>
`cvtColor(source image,destination image,code,dstCn)`<br/>
In **`code`** which is int value we define from which color space to which we want to change for example if we want to change from BGR to HSV we can simpy put the code **`COLOR_BGR2HSV`**<br/>

_Threshold_<br/>
In this, if the pixel value is greater than threshold value then one of the thresholding type is to be applied.<br/>
'threshold(source image, destination image , threshold value, max value, type)`<br/>
There are 5 types of thresholding <br/>
- Threshold Binary: If pixel value is greater than threshold then assign those max value and pixel whose value is smaller than threshold assign it to zero.
- Threshold Binary, Inverted: It is inverse of Threshold Binary.
- Truncate: If pixel value is greater than threshold then assign those threshold value to the pixel and whose value is smaller than threshold leave pixel as it is.
- Threshold to Zero: If pixel value is greater than threshold then leave pixel as it is and pixel whose value is smaller than threshold assign it to zero.
- Threshold to Zero, Inverted: It is inverse of Threshold to Zero.

_Bluring and Smoothing_<br/>
Some time while during image processing it is unecessary to provide every detail of an image. If every detail of the image is provided then it might acts as noise . So we need to blur and smooth out the image.<br/>
In order to blur the image we use kernel.**Kernel** is simply matrix smaller than your original image. Inside the kernel there is numerical value and kernal must be square matrSix with odd numbers of sides.Kernel change value of pixel by combining it with different amount of neighbouring pixels.It is applied to each and every pixels one by one to produce final pixel.[More about kernels](https://github.com/atduskgreg/opencv-processing-book/blob/master/book/filters/blur.md)<br/>
- **Gaussian Blur**<br/> In gausian blur , we use normal distribution central pixel has higher weight in the given kernal and further we deviate from the central pixel in the kernal value decreases. It is determine by the standard deviation. Higher deviation, value of other pixel will be close enough to the central pixel and smaller the deviation lesser the value.

