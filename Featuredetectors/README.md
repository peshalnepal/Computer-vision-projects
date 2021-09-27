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

SIFT Feature Descriptor output to match features <br/>
[Descriptor output ](photos/output_descriptor.png)

Keypoints on the supplied images using SURF algorithm<br/>
[Keypoints on the image](photos/output_surf.png)

[Keypoints on the image 1](photos/output_1_surf.png)

SURF Feature Descriptor output to match features <br/>
[Descriptor output ](photos/output_descriptor_surf.png)

## FEATURE DETECTORS

---
## SIFT Feature Detector
SIFT feature detector stands for Scale-Invariant Feature Transform. In this, keypoints is extracted along with its orientation and descriptor is define for every keypoints so that scale as well as rotation of the image won't affect the keypoints. It contains of multiple steps where either keypoint is calculated, noise is removed from the keypoint, orientation is calculated for the keypoint or descriptor is created for respective keypoint. Followings are the steps taken to calcuate feature vector for the image.
- **Scale-space peak selection:**
  - Scale space:<br/>
    Two similar images can be vary vastly in various ascpect. Images can be for different sizes. In one Image objects might be closer than other image. Orientation of image or objects might not be same. So we need to consider those as even though image is rotated they are image of same thing so features of object detected in one image must be similar to that of another similar image. So Scale space invarient method is used where image of same size is blurred at different scale (sigma value)
  
  - Blurring:<br/>
    In space scale invarient method, we blurred image at different scale(sigma value). In order to blur, we convolve our input image with Gaussian kernel at different scale and different sigma value.
    
    $`\large\\ 
     \begin{aligned}
     &L(x,y,\sigma)=G(x,y,\sigma)*I(x,y)\\
     &\textcolor{gray}{Blured image}
     \end{aligned}\\
     `$

     G is the Gaussian Blur operator and I is an image. While x,y are the location coordinates and σ is the “scale” parameter. Think of it as the amount of blur. Greater the value, greater the blur.

     $`\large\\
     \begin{aligned}
     &G(x,y,\sigma)={\frac {1}{2\pi \sigma^2 }}e^{-{\frac {x^2-y^2 }{2\sigma^2 }}}\\
     &\textcolor{gray}{Gaussian Blur operator}
     \end{aligned}
    `$
    
    Images blurred with different sigma value and are called scale of the image. Images are reduce to half of its original size for every octave. So, basically for each input image, there will be scale of images with same size but blurred at different level in each octave. 
    
  - Difference of Gaussian kernel (DOG):<br/>
    Specially laplacian of Gaussian is used for extracting features of image. But instead of Laplacian of Gaussian we use Difference of Gaussian which produce similar type of result. <br/>
    In Difference of Gaussian, Blurred images of similar size but different blurring scale are subtracted from one another to extract the the features or keypoints in the image. 

    $`D\left(x,y,\sigma \right)=L\left(x,y,k_{i}\sigma \right)-L\left(x,y,k_{j}\sigma \right)`$

    where $` L(x,y,k\sigma)`$ is the convolution of the original image Ix,y) with the Gaussian blur{\displaystyle $`G(x,y,k\sigma)`$ at scale $`k\sigma`$

    Difference of Gaussian between scales $`k_{i}\sigma`$  and $`k_{j}\sigma`$  is just the difference of the Gaussian-blurred images at scales $`k_{i}\sigma`$  and $`k_{j}\sigma`$.
  
  - Finding Keypoints:<br/>
    After possible features that are extracted, there can be possiblity of noise so noises are to be the removed before going any further so any pixels value smaller than 0.03 are removed. One pixel in an image is compared with its 8 neighbors as well as 9 pixels in the next scale and 9 pixels in previous scales. If the keypoints is local maxima or local minima then they are consider as keypoint otherwise thery are discarded.
  
- **Keypoint Localization :**<br/>
  Obtained keypoints are not noise free as some still lack proper intensities and some lie at the edges. So we need to remove those. Alsoe location of some of the keypoints are not accurate. So Interpolation needs to be done.<br/>
  To interpolate the location of keypoint accurately we used Taylor series expansion of the Difference of Gaussian i.e.

  $`{\displaystyle D({\textbf {x}})=D+{\frac {\partial D}{\partial {\textbf {x}}}}^{T}{\textbf {x}}+{\frac {1}{2}}{\textbf {x}}^{T}{\frac {\partial ^{2}D}{\partial {\textbf {x}}^{2}}}{\textbf {x}}}`$

  Here D(x) is intensity of interpolated pixel. To calculate the value by which we needs to move the keypoint.
  
  $`\large
  \begin{aligned}
  &h= -H^-1(x)\frac{dD}{dx}\\
  &where,\\
  &H(x)=\begin{bmatrix}
  D_{xx}&D_{xy}&D_{x\sigma}\\
  D_{xy}&D_{yy}&D_{y\sigma}\\
  D_{x\sigma}&D_{y\sigma}&D_{\sigma\sigma}
  \end{bmatrix}
  \\
  &\frac{dD}{dx}=\begin{bmatrix}
  \frac{dD}{dx}\\
  \frac{dD}{dy}\\
  \frac{dD}{d\sigma}
  \end{bmatrix}
  \end{aligned}
  `$

  D(x) further simplifies to

  $`D(x)=D+\frac{1}{2}\frac{\partial D}{\partial x}.h`$
  
  By calculating value of h we can get value by which x and y value is to be moved. And it is added to the keypoints co-ordinate. If interpolated pixel value i.e. **D(x)<=0.03** then it is discarded.

  Filter and interpolated keypoints still contains keypoints at the edge which should be removed. It is done by calculating eigen value of Hessian matrix.

  $`
  \begin{aligned}
  &H(x)=\begin{bmatrix}
  Dxx & Dxy\\ 
  Dyx & Dyy
  \end{bmatrix}\\
  &(Dxx+Dyy)^2/(Dxx*Dyy-(Dxy)^2)=(1+r)^2/r
  \\
  &r=\frac{\alpha}{\beta}=\frac{eigen\_value\_1}{eigen\_value\_2}
  \end{aligned}
  `$

  To remove the edge, If keypoint satisfies r>10 then it is consider as keypoint other wise it is removed. 