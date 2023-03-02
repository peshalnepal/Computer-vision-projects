# Read a video and convert it to a video of half size and double the framerate
## Description:

In this project, video is read from the given path and converted into video of double framerate and half size.

## Prerequisites:
- opencv is required to run this project and if not install follow previous documentation on logistic setup 
- camke is also needed and if not install in your device you can use following syntax to install <br/>
  ***`sudo apt-get install cmake`*** 

## Run the project
- Download the code from the Git
- open the folder you just downloaded in terminal , it contains other folders and files 
- Run ***`cmake -S . -B .`*** command
- After this, Run ***`make`*** command
- executable name **ReadVideo** has been created 
- To check the output, Run ***`./ReadVideo`*** command in terminal
- If user want to convert to specific video the path to the video with name and extension should be pass in **`./ReadVideo pathtothevideo/videoname.extension`**
- To close all the window press key **'esc'** from the keyboard or windows will close automatically after video ends

## Input & Output: <br/>
Orginal video used in this project is of height 720px and width 1280px with frame rate of 30fps <br/>
Orignal video can be found in the givn location `videos/check.mp4`

Final video is of height of 360px and width of 640px with frame rate of 60 fps <br/>
Final converted video can be found in the givn location `videos/output.mp4`

## About Videos:

Videos are just sequence of images. Each Videos are made up of images which changes number of times in second. Images in videos are called frames. Number of times frame changes in a second in video gives frames per second or fps. Higher fps smoother will be the video. Video format is determine by codec and container. <br/>
Codec determines how videos are encoded and decoded. Codec are determined by hardware, software, algorithm used. Codec used to encode data to store videos in DVD is different than codec used in tap recorder. Codecs are also responsible for compressing the video files.<br/>
Container is responsible for storing compressed or uncompressed video file , with its audio and subtitle with some metadata. Container define extension of video file.<br/>
Output of Different codes can be store in different conatiners and each codec used for encoding and decoding purspose is represented by 4 1byte character. For example `XVID` is codec which is used for linux system whose converted ouput is store in `avi` container as a result obtain file will be of extension `.avi` 


## Read Video file using Opencv
**Syntax:**</br>

`VideoCapture videoCapture (const String &filename);` <br>
`VideoCapture videoCapture (int index);` </br>

In order to capture video we use `VideoCapture` class contained in opencv. Here in first syntax we are passing video filename and filepath so that we can read spefici video. We create `videoCapture` object of `VideoCapture` which can be used further in our project to read each frames from our video and store it in Mat object we create<br/>
In second syntax rather than passing actual video file path we pass the index value which denote the camera attach with your device from which user want to capture the video rather than video file. To open default camera using default backend just pass 0.<br/>

**Syntax:**</br>

``Mat img;<br>
videoCapture.read(img);``

This syntax read video frame by frame and store it as Mat object. As video is sequence of images, So this function must be kept inside infinte loop to read each and every frame.

## Write Video file using Opencv
**Syntax:**<br/>
`VideoWriter videoWriter(const String &filename, int fourcc, double fps, Size frameSize, bool isColor=true)`<br>

To write video to the disk we use VideoWriter class . Object of this class is responsible for writing each frame of the video . While creating object we also pass the name, path and extension of output video. We also pass Codec which can be used to code and decode video . Each code is represented by 4 character 1 byte each . Those four character are pass into fourcc function from VideoWriter in following way.<br/>
`Videowriter::fourcc(char1,char2,char3,char4)`<br/>
If we are storing image in **mp4 container** We need to pass `"m","p","4","v"`  in place of those four characters.<br/>
We can write in video in any fps and at any size which can be passed as other parameters. `isColor` is bool which set to true if we want to write color image and false if we want to write grayscale image

**Syntax:**<br/>
`videoWriter.write(img);`

This syntax wrtie any thing from the Mat obj `img` in output video file. One thing to keep in mind, Size of img must match with frameSize describe while creating VideoWriter object.

To read more about Codec follow the provided link below:
[Video tutorial about Codec](https://www.youtube.com/watch?v=-4NXxY4maYc)
[ About Fourcc](https://www.fourcc.org/codecs.php)

To read more about Video I/O follow the provided link:
[About Video I/O](https://docs.opencv.org/3.4/dd/de7/group__videoio.html)