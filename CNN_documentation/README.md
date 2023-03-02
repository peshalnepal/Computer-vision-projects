# Describing different NN archictures and comparining their perfomance
## RCNN
RCNN stands for Region-Based Convolutional Neural Network. As for any Convolutional neural network it is easy task for image classification but when it comes to localizing and detecting object it is not pretty good at it. User need to pass the region of interest to where look for the objects.

In RCNN , selective search method is used for genrating near about 2000 bounding boxes which are then passed to convolutional neural network for extracting 4096 feature vectors which are then passed into the Support Vector Machine (SVM) for output if there is object in the region or not. Not only that final output consist of boundary value which offsets the predicted region. 

The problems with RCNN are:

- selective search algorithm is algorithm with parameters which can not be trained it is fix algorithm. 
- It can not be implemented in real time as it takes about 47 sec to process single image. 
- Near about 2000 region per image needs to be classify before training for single image. 
  
## Fast RCNN
Fast RCNN is made on top of SPPNet architecture. Instead of using region proposal in the input image such as in region proposal for training purposes. The proposed regions are used in the feature map to extract the feature vectors.

Fast RCNN architecture consists of the Region proposal part which generates probable regions. The images are passed through the dense convolutional layers which generate feature maps. The detected Region on the images are mapped into the size of feature maps and the region where the region is mapped is taken into account for ROI pooling. For each Feature map ROI pooling is applied. 

### ROI pooling
ROI pooling is just max-pooling whose output size does not depend upon input. It is of the same size and does not rely on input images.

The output of the ROI pooling layer is a fixed-size feature vector obtained from the feature map. Feature vectors are passed into a fully connected layer that finally branch into two sibling output layer. One of the sibling layers produces softmax probability estimates over k object classes plus background and another layer that outputs four real-valued numbers for each of the k object classes.The loss in Fast RCNN is smooth L1 loss calculated over both the sibling layers and is used for backpropagation

Loss function used in Fast RCNN

$`L(p_i,t_i)=\sum_i {L_{cls}(p_i,{p_i}^*)}+\lambda *\sum_i{p_i*L_{reg}(t_i,{t_i}^*)}\\
\text{where ,}
p_i \text{is confidenece score of ground truth}\\
{p_i}^* \text{is confidenece score of ground truth} \\
t_i \text{is actual offset of proposal area from the ground truth} \\
{t_i}^* \text{is predicted offset of proposal area from the ground truth}`$

If predicted region doesnot contain the object then its loss function is not necessary to caculate and will be unused. 

### Results of Fast-RCNN
- Training is 9x faster than R-CNN. While inference Fast R-CNN is 213x faster than R-CNN. Similarly using VGG16, Fast R-CNN is 3x faster while training and 10x faster while inference compared to SPP Net.
- mAP on VOC-2007–12 dataset achieves 71.8%. On COCO Pascal-style mAP is 35.9. The new coco-style mAP, which averages over IoU thresholds, is 19.7% on coco dataset
  
## Faster RCNN
Faster RCNN is one of the Regional Convolutional Neural Network which used two deep Convolutional network one for proposing a region and another is Fast RCNN which uses proposed region. Region Proposal network is used for identifying the region and its output is passed on to Fast RCNN module. This is way faster than traditional selective search. The idea of Anchor boxes was used in this algorithm.  

### Region Proposal Network
RPN takes an image as input and outputs a set of rectangular object proposal each with objectness score. The Feature map obtained at last convolutional layers of ZF model or VGG-16 model is passed onto the RPN. 

Sliding window is passed over the feature map of size n\*n which is responsible for mapping the input the lower dimension of size 256-d for ZF and 512-d for VGG. The output of the sliding window is passed into two sibling 1\*1 convolutional layer where one is bounding box classification layer and another is bounding box regression model.

For Each sliding window, multiple anchor boxes are associate with them each of them have different aspect ratio and scale. In Faster RCNN there are total of 9 anchor boxes i.e. anchor boxes of 3 different scales and sizes are used. For regression layer we have 4k outputs enchoding the output of k anchor boxes and 2k for classification layer. Perviously instead of using anchor boxes of different sizes filter sizes or image sizes were reduced to identify objects of different dimension. But using anchor boxes single feature map with a single filter can give all the required information.

Even though each pixels location has 9 anchor boxes associated with them every anchor boxes might not give the location of an object or might not contain object in them so two sibling layers classify and localizes these anchor boxes. Bounding box classification layer will classify whether there is foreground or backgorund in the image where as Bounding Box regression layer will provides the offset value of anchor boxes with the gorund truth bounding box. Near about 2000 proposal regions are obtained at end of the RPN network and Non Max supression is used to obtain N top proposal regions for further passing into Fast RCNN module .

### Results of Faster-RCNN
- Inference with 5fps in GPU
- Using VGG backend, with pretraining on ImageNet and COCO, On VOC Faster RCNN achieved 73.2% mAP (mean Average Precision).

## YOLO  

YOLO algorithm stands for You Only Look Once. Single CNN simultaneously predicts multiple bounding boxes and class probability for those boxes. Images are divided into grid cells and if the center of the object lies in the grid cell then it is responsible for detecting the object. Each Grid cell predicts bounding boxes and for each bounding boxes if there exists an object then their confidence score is also measured which should equal the IoU between the Ground truth bounding box and predicted bounding box. Each grid cell has an output of confidence score, predicted bounding box coordinate, and their width and height. The Anchor boxes around the region is compared with the predicted bounding boxes and if the IoU is above some threshold value then the class of the predicted bounding box is assigned to the Anchor boxes and the error in center coordinate and width and height of the predicted bounding box with the anchor boxes is measured. Multiple Anchor boxes are measured at the same location so Iou is measured with all predicted anchor boxes and if the IoU is above some threshold only the anchor box with a high confidence value is kept and others are discarded.

YOLO consists of 24 convolutional neural networks with two fully concerted neural networks which are responsible for outputting 7\*7\*30 tensor.  
Initial Conv layers of neural network extract feature whereas fully connected layers predict the output probabilities and coordinates. Activation function leaky ReLU is all the layers and sum of squared error is used as Loss function. YOLO predicts multiple bounding boxes per grid cell. At training time we only want one bounding box predictor to be responsible for each object. The predictor which is responsible for identifying the object is obtained from IOU with the ground truth. 
IOU is an intersection over union and is used to measure the overlap of predicted bounding box over ground truth bounding box. higher IOU means higher is the overlap.
CNN model can output the bounding boxes around the objects but due to the shared weights, it is difficult to exactly pinpoint the object location so anchor boxes are used. 
Anchor boxes are placed around the grid cells and offset to the anchor boxes are measured for training purposes instead of actual coordinates. 
To use anchor box and offset of Anchor box from the ground truth. IOU of anchor boxes with ground truth is calculated and the anchor box is assigned the same class label as the ground truth bounding box if the IOU between those two is the highest. The same is done for the remaining ground truth bounding box. 
The offset of Anchor boxes to their ground truth is calculated and used for training purposes. 
While predicting the location of an object, multiple anchor boxes are predicted for the same object. IOU between Anchor boxes is calculated and if it is above some threshold values the anchor box with the highest confidence value is kept and others are discarded.

### Results of YOLO
- YOLO is extremely Fast and works at 45 frames per second 
- YOLO using DarkNet achieves an mAP of 63.4 at 45 frames per second. mAP is far less compared to Faster R-CNN using VGG-16 (73.2) but the speed of Faster R-CNN is at 7 frames per second. The Fast R-CNN framework achieves an mAP of 71.8% at 0.5 FPS (frames per second).
- Since the model predicts bounding boxes from data, it struggles to generalize to objects in new or unusual aspect ratios and configurations.
- Yolo is better at making less localization errors as it looks at the entire image to predict objects on individual cells. So Yolo captures and considers global features of the entire image for predicting for individual cells, which is not the case with Faster R-CNN. A survey on the errors found that Fast R-CNN almost make 3x background errors compared to Yolo. So for every bounding box the Fast R-CNN predicts, it is again evaluated by the Yolo. This improved the mAP of Fast R-CNN by 3.2% to 75%.

## Mask RCNN 
Mask RCNN is implemented on top of Faster RCNN and output of Mask RCNN is instance segmentation. Mask RCNN shared same architecture as that of Faster RCNN  with CNN of semantic segmentation. Mask RCNN solve the problem of instance segmentation as it segment individual object which lies under the same class. 

The image pooled using the ROI pooling are quantized in previous image segmentation task but in Mask RCNN ROI align is used as a result quantization of the output is not to be performed. ROI is aligned the result obtained are passed to FCN conv and Deconv of the ROI aligned output will gives us the Mask for each class of size m\*m for each ROI feature map. 

### Results of Mask RCNN 
- Works pretty well with 200m/s/img i.e 5 frames per second. 
- Average precision of 37.1 is obtained. 
  
For Further study
- [About Support Vector Machine](https://towardsdatascience.com/support-vector-machine-introduction-to-machine-learning-algorithms-934a444fca47)
- [Paper in selective search algorithm](https://ivi.fnwi.uva.nl/isis/publications/2013/UijlingsIJCV2013/UijlingsIJCV2013.pdf)
- [Video Lecture in image detection and segmentation](https://www.youtube.com/watch?v=nDPWywWRIRo)
- [Video lecture for understanding and visualizing CNN](https://www.youtube.com/watch?v=6wcs6szJWMY)
- [RCNN, Fast RCNN, Faster RCNN and YOLO](https://towardsdatascience.com/r-cnn-fast-r-cnn-faster-r-cnn-yolo-object-detection-algorithms-36d53571365e)
- [Paper on Fast RCNN](https://arxiv.org/pdf/1504.08083)
- [Anchor Boxes](https://www.wovenware.com/blog/2020/06/anchor-boxes-in-object-detection-when-where-and-how-to-propose-them-for-deep-learning-apps/#.YaWuWpF1hNi)
- [Implementation of RCNN, Fast RCNN and Faster RCNN](https://medium.com/@fractaldle/brief-overview-on-object-detection-algorithms-ec516929be93)
- [Paper on Faster RCNN](https://arxiv.org/pdf/1506.01497)
- [Study about Region Proposal Network](https://towardsmachinelearning.org/region-proposal-network/)
- [Paper On YOLO](https://arxiv.org/abs/1506.02640)
- [Video on YOLO and Anchor boxes](https://www.youtube.com/watch?v=vRqSO6RsptU&t=1164s)
- [About Mask RCNN](https://alittlepain833.medium.com/simple-understanding-of-mask-rcnn-134b5b330e95)
- [paper on Mask RCNN](https://arxiv.org/pdf/1703.06870)