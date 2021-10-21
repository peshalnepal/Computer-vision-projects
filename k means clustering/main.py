import pandas as pd
import numpy as np
from pandas import DataFrame
from keras.datasets import mnist
from sklearn import metrics
# import seaborn as sns
import sys
sys.path.insert(0,'./src/')


from clustering import KMeansClustering
# load mnist Dataset
(X_train_original,Y_train),(X_test,Y_test)=mnist.load_data()


# Data preprocessing
######################
######################
# normalize dataset between 0 and 1 
X_train_original=X_train_original.astype(np.float32)
X_test=X_test.astype(np.float32)
X_train_original=X_train_original/255.0
X_test=X_test/255.0



# Reshaping 2D image to 1D format 
# From 28*28 to 784
X_train=X_train_original.reshape((len(X_train_original),-1))
X_train.shape

# out of 60000 images only 3000 images is used 
X_train=pd.DataFrame(X_train[0:3000])
Y_train=Y_train[0:3000]
K=len(np.unique(Y_test))

# fitting the data and training the model 
model_=KMeansClustering(K,num_iter=100)
labels=model_.fit(X_train)

# cluster may have different labels from its actual labels
# so to calculate actual label for cluster using following function
def get_label(labels_,y_train):
    reference_labels = {}
    for i in range(len(np.unique(labels_))):
        index = np.where(labels_ == i,1,0)
        num = np.bincount(y_train[index==1]).argmax()
        reference_labels[i] = num
    new_labels=np.zeros(len(labels_))
    for i in range(0,len(new_labels)):
        new_labels[i]=reference_labels[labels_[i]]
    return new_labels
    
    
new_labels=get_label(labels,Y_train)

# Calculating error metrics and plotting the heatmap
cf_matrix=metrics.confusion_matrix(Y_train, new_labels, labels=[0,1,2,3,4,5,6,7,8,9])
print("confusion matrix \n",cf_matrix)
print(metrics.classification_report(Y_train, new_labels, labels=[0,1,2,3,4,5,6,7,8,9],zero_division=0))
# heatmap=sns.heatmap(cf_matrix, annot=True)
# heatmap.get_figure()
# heatmap.savefig("photos/heatmap.png")
