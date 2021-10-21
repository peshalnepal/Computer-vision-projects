import pandas as pd
import numpy as np
from pandas import DataFrame
## Implementation of kmeans clustering Algorithm
################################################
class KMeansClustering:
    def __init__(self,K,num_iter) -> None:
        self.num_iter=num_iter
        self.K=K
            
    def fit(self,X_train):
        inital_values=np.array(X_train.sample(self.K))
        variation=1
        # To store cluster label for each image
        labels=np.zeros((len(X_train)))
        print(len(X_train))
        a=0
        while variation>0.1 or a<self.num_iter:
            variation=0
            labels=np.zeros((len(X_train)))
            number_datas=np.zeros(self.K)
            for i in range(0,len(X_train)):
                cluster_loc=0
                compare_distance=10000
                for j in range(0,self.K):
                    # calculate distance between points and cluster centroid and assign points to the cluster based on smallest distance 
                    # of points from centroid of cluster
                    dist_btw_points=np.linalg.norm(np.array(X_train.iloc[i])-inital_values[j])
                    if(compare_distance>dist_btw_points):
                        compare_distance=dist_btw_points
                        cluster_loc=j
                labels[i]=cluster_loc
                number_datas[cluster_loc]+=1
            total_sum= np.zeros(inital_values.shape)
            # calculate centroid of the cluster using average
            for i in range(0,len(X_train)):
                location=int(labels[i])
                total_sum[location]=total_sum[location]+np.array(X_train.iloc[i])
            mean_sum=total_sum / number_datas[:,None]
            for i in range(0,self.K):
                variation+=np.linalg.norm(mean_sum[i]-inital_values[i])
            inital_values=mean_sum
            a+=1
        return labels
        