import cv2
import numpy as np
import matplotlib.pyplot as plt
import sys, os

def showimage(img): 
    fx=plt.figure(figsize=(20,20))
    ax=fx.add_subplot(111)
    ax.imshow(img,cmap="gray",vmax=255,vmin=0)
    
def nonmaxsupress(demoimage,demoangle):
    a=2
    b=1
    imgfinal=np.zeros((demoimage.shape[0]+a,demoimage.shape[1]+a))
    angle=np.zeros((demoangle.shape[0]+a,demoangle.shape[1]+a))
    imgfinal[b:demoimage.shape[0]+b,b:demoimage.shape[1]+b]=demoimage
    angle[b:demoangle.shape[0]+b,b:demoangle.shape[1]+b]=demoangle
    num_rows, num_cols = imgfinal.shape
    # here each pixel is check with its neighboring pixel values
    # if angle associated with the pixel lie between 0 to 22.5 degree then pixel is compared with pixels in vertical direction
    # Similar goes for horizontal and diagonal direction
    for i in range(b,num_rows):
        for j in range(b,num_cols):
            if imgfinal[i][j]>0:
                arraycreated=imgfinal[i-b:i+1+b,j-b:j+1+b]
                if angle[i][j] >= 67.5 and angle[i][j] <= 112.5:
                    if imgfinal[i][j]!=np.max(arraycreated[:,b]):
                        imgfinal[i][j]=0
                    else:
                        imgfinal[i,j]=np.sum(arraycreated[:,b])
                elif (angle[i][j] >= 0 and angle[i][j] <= 22.5) or (angle[i][j] >= 157.5 and angle[i][j] <= 180.0):
                    if imgfinal[i][j]!=np.max(arraycreated[b,:]):
                        imgfinal[i][j]=0
                    else:
                        imgfinal[i][j]=np.sum(arraycreated[b,:])
                elif angle[i][j] >= 22.5 and angle[i][j] <= 67.5:
                    if imgfinal[i][j]!=np.max(arraycreated.diagonal()):
                        imgfinal[i][j]=0
                    else:
                        imgfinal[i][j]=np.sum(arraycreated.diagonal())
                elif angle[i][j] >= 112.5 and angle[i][j] <= 157.5:
                    if imgfinal[i][j]!=np.max(np.fliplr(arraycreated).diagonal()):
                        imgfinal[i][j]=0
                    else:
                        imgfinal[i][j]=np.sum(np.fliplr(arraycreated).diagonal())
            else:
                imgfinal[i][j]=0
    return imgfinal,angle

def doublethres(imgfinal,lower_,upper_,angle):
    rows,columns=angle.shape
    # if pixels lie in horizontal edge then angle associated with it lie in between 67.5 to 112.5 degree
    # Pixel value is checked in this function
    # If pixel value is greeater than upper_ then it is assign to 255.0 
    # If pixel value is smaller than lower_ then it is assign to zero
    # Any pixel that lie in between upper_ and lower_ are assign to 0 or 255.0 based to their neighboring pixels/
    # If pixel value lie in between those two values and lie in horizontal edge then neighboring pixel which are attach with pixel in horizontal direction are checked
    # if it is greater than 255.0 then this pixel is assign to 255.0 else 0
    for i in range(0,rows-1):
        for j in range(0,columns-1):
            if(imgfinal[i,j]>=upper_):
                imgfinal[i,j]=255.0
            elif(imgfinal[i,j]<=lower_):
                imgfinal[i,j]=0.0
            else:
                if angle[i][j] >= 67.5 and angle[i][j] <= 112.5:
                    if imgfinal[i][j-1]>=upper_ or imgfinal[i][j+1]>=upper_:
                        imgfinal[i][j]=255.0
                    else:
                        imgfinal[i][j]=0.0
                elif (angle[i][j] >= 0 and angle[i][j] <= 22.5) or (angle[i][j] >= 157.5 and angle[i][j] <= 180.0):
                    if imgfinal[i-1][j]>=upper_ or imgfinal[i+1][j]>=upper_:
                        imgfinal[i][j]=255.0
                    else:
                        imgfinal[i][j]=0.0
                elif angle[i][j] >= 22.5 and angle[i][j] <= 67.5:
                    if imgfinal[i+1][j-1]>=upper_ or imgfinal[i-1][j+1]>=upper_:
                        imgfinal[i][j]=255.0
                    else:
                        imgfinal[i][j]=0.0
                elif angle[i][j] >= 112.5 and angle[i][j] <= 157.5:
                    if imgfinal[i-1][j-1]>=upper_ or imgfinal[i+1][j+1]>=upper_:
                        imgfinal[i][j]=255.0
                    else:
                        imgfinal[i][j]=0.0
    return imgfinal

def sobelconvolution(img,hvkernel):
    [rows,columns]=img.shape
    finalimg=np.zeros(shape=(rows,columns))
    print("img_shape",img.shape)
    print("final_shape",finalimg.shape)
    for i in range(0,rows-2):
        for j in range(0,columns-2):
            finalimg[i+1,j+1]=np.sum(np.multiply(hvkernel, img[i:i + 3, j:j + 3]))
    
    return finalimg

def cannyedge(img,lower_,upper_):
    # In this all steps involve in cannyedge detection are performed
    # at first sobelfilter is applied to the image 
    # to perform sobel filter vertical edge detection kernel store in verticaledge variable is passed to sobelconvolution function along with the image and output is store in img1
    verticaledge=np.array([[-1,0,1],[-2,0,2],[-1,0,1]],np.float32)
    horizontaledge=np.array([[1,2,1],[0,0,0],[-1,-2,-1]],np.float32)
    # img1 contain image after applying verticaledge detection filter to the image
    img1=sobelconvolution(img,verticaledge)
    # img2 contain image after applying verticaledge detection filter to the image
    img2=sobelconvolution(img,horizontaledge)
    # angle to identify wether pixel lie in hoizontal, vertical, or diagonal edge can be found using np.arctan2()
    angle=np.arctan2(img2,img1)
    angle = np.degrees(angle)
    angle[angle < 0] += 180.0
    angle=np.resize(angle,img.shape)
    # final output image is obtain after sqauring img1 & img2, adding the obtain result and square rooting 
    imgfinal=np.hypot(img1,img2)
    # this function perform non maxsupression used for thinning out edges
    imgfinal,angle= nonmaxsupress(imgfinal,angle)
    # this functionapplu double thresholding to remove unwanted edges
    imgfinal=doublethres(imgfinal,lower_,upper_,angle)
    return imgfinal

def convoltion_(img,kernel):
    imgrow,imgcolumn=img.shape
    kernelrow,kernelcolumn=kernel.shape
    finalimage=np.zeros(shape=(imgrow+kernelrow-1,imgcolumn+kernelcolumn-1))
    padding_row=(kernelrow-1)//2
    padding_column=(kernelcolumn-1)//2
#     finalimage[padding_row:padding_row+imgrow,padding_column:padding_column+imgcolumn]=img
    final_row,final_column=finalimage.shape
    for i in range(0,imgrow-kernelrow+1):
        for j in range(0,imgcolumn-kernelcolumn+1):
            finalimage[i+padding_row,j+padding_column]=np.sum(np.multiply(kernel, img[i:(i + kernelrow),j:(j + kernelcolumn)]))
    gamma=1.1
    finalimage=np.power(finalimage,gamma)
    return finalimage

def gaussianBlur(image,filtershape,sigma):
    # In this function gaussian blur is applied in the image
    # Here filter of provided size describe inside variable filtershape is created containing all zeros
    gaussianfilter=np.zeros(shape=(filtershape,filtershape))
    # As middle part of kernel should have bigger value than corners so middle pixel of kernel is determine
    m=filtershape//2
    n=filtershape//2
    # As formula for gaussian filter has maximum value when both x and y value is zero
    # As we need to make central pixel of higher weight so we are starting our loop form -m rather than 0
    for i in range(-m,m+1):
        for j in range(-n,n+1):
            value1=2*np.pi*sigma**2
            value2=np.exp(-((i)**2+(j)**2)/(2*sigma**2))
            gaussianfilter[m+i][n+j]=value2/value1 
    finalimg=convoltion_(image,gaussianfilter)
    return finalimg
    
def main():
    path=""
    try:
        if (len(sys.argv)>1):
            path=sys.argv[1]
        else:
            path="photos/img.png"  
        # print(path)
        originalimg=cv2.imread(path,cv2.IMREAD_COLOR)
        if originalimg is None:
            raise Exception
    except Exception as e:
        print("Image not found in the provided path")
        return 0
    else:
        originalimg=cv2.cvtColor(originalimg,cv2.COLOR_BGR2GRAY)
        img =gaussianBlur(originalimg,5,2)
        img=img/img.max()*255
        img=img.astype("uint8")
        medianimg=np.median(img)
        lowerthres=float(max(0,0.7*medianimg))
        upperthres=float(min(255,1.3*medianimg))
        finalimage=cannyedge(img,lowerthres,upperthres)
        cannyimage=cv2.Canny(img,lowerthres,upperthres)
        while True:
            displayedgedetectedimg=cv2.imshow("edge detected image",finalimage)
            displayfunctionimg=cv2.imshow("prebuilt fucntion image",cannyimage)
            displayblurimg=cv2.imshow("blur image",img)
            displayoriginalimg=cv2.imshow("original image",originalimg)
            if cv2.waitKey(1) & 0xFF==27:
                cv2.imwrite("photos/outputblur.png",img)
                cv2.imwrite("photos/outputfromscratch.png",finalimage)
                cv2.imwrite("photos/outputfromfucntion.png",cannyimage)
                break
        cv2.destroyAllWindows()

if __name__=="__main__":
    main()