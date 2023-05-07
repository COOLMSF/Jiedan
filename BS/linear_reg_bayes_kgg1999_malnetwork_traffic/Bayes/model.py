import numpy as np 
import pandas as pd
import warnings

from sklearn.model_selection import train_test_split

import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import time

from sklearn.metrics import accuracy_score
from sklearn.linear_model import LinearRegression, GaussianNB
from sklearn.metrics import confusion_matrix

class Bayes:
    data = None
    
    def __init__(self):
        warnings.filterwarnings('ignore')
        pd.set_option('display.max_columns', None)
        pd.set_option('display.max_rows', None)
        cols = [' Destination Port', ' Flow Duration', ' Total Fwd Packets',
               ' Total Backward Packets', 'Total Length of Fwd Packets',
               ' Total Length of Bwd Packets', ' Fwd Packet Length Max',
               ' Fwd Packet Length Min', ' Fwd Packet Length Mean',
               ' Fwd Packet Length Std', 'Bwd Packet Length Max',
               ' Bwd Packet Length Min', ' Bwd Packet Length Mean',
               ' Bwd Packet Length Std', 'Flow Bytes/s', ' Flow Packets/s',
               ' Flow IAT Mean', ' Flow IAT Std', ' Flow IAT Max', ' Flow IAT Min',
               'Fwd IAT Total', ' Fwd IAT Mean', ' Fwd IAT Std', ' Fwd IAT Max',
               ' Fwd IAT Min', 'Bwd IAT Total', ' Bwd IAT Mean', ' Bwd IAT Std',
               ' Bwd IAT Max', ' Bwd IAT Min', 'Fwd PSH Flags', ' Bwd PSH Flags',
               ' Fwd URG Flags', ' Bwd URG Flags', ' Fwd Header Length',
               ' Bwd Header Length', 'Fwd Packets/s', ' Bwd Packets/s',
               ' Min Packet Length', ' Max Packet Length', ' Packet Length Mean',
               ' Packet Length Std', ' Packet Length Variance', 'FIN Flag Count',
               ' SYN Flag Count', ' RST Flag Count', ' PSH Flag Count',
               ' ACK Flag Count', ' URG Flag Count', ' CWE Flag Count',
               ' ECE Flag Count', ' Down/Up Ratio', ' Average Packet Size',
               ' Avg Fwd Segment Size', ' Avg Bwd Segment Size',
               ' Fwd Header Length.1', 'Fwd Avg Bytes/Bulk', ' Fwd Avg Packets/Bulk',
               ' Fwd Avg Bulk Rate', ' Bwd Avg Bytes/Bulk', ' Bwd Avg Packets/Bulk',
               'Bwd Avg Bulk Rate', 'Subflow Fwd Packets', ' Subflow Fwd Bytes',
               ' Subflow Bwd Packets', ' Subflow Bwd Bytes', 'Init_Win_bytes_forward',
               ' Init_Win_bytes_backward', ' act_self\.data_pkt_fwd',
               ' min_seg_size_forward', 'Active Mean', ' Active Std', ' Active Max',
               ' Active Min', 'Idle Mean', ' Idle Std', ' Idle Max', ' Idle Min',' Label']
        
        df1=pd.read_csv("../../self\.dataset/MachineLearningCSV/MachineLearningCVE/Friday-WorkingHours-Afternoon-DDos.pcap_ISCX.csv", usecols = cols)#,nrows = 50000
        df2=pd.read_csv("../../self\.dataset/MachineLearningCSV/MachineLearningCVE/Friday-WorkingHours-Afternoon-PortScan.pcap_ISCX.csv", usecols = cols)
        df3=pd.read_csv("../../self\.dataset/MachineLearningCSV/MachineLearningCVE/Friday-WorkingHours-Morning.pcap_ISCX.csv", usecols = cols)
        df4=pd.read_csv("../../self\.dataset/MachineLearningCSV/MachineLearningCVE/Thursday-WorkingHours-Afternoon-Infilteration.pcap_ISCX.csv", usecols = cols)
        df5=pd.read_csv("../../self\.dataset/MachineLearningCSV/MachineLearningCVE/Thursday-WorkingHours-Morning-WebAttacks.pcap_ISCX.csv", usecols = cols)
        
        df = pd.concat([df1,df2])
        del df1,df2
        df = pd.concat([df,df3])
        del df3
        df = pd.concat([df,df4])
        del df4
        df = pd.concat([df,df5])
        del df5
        
        self.data = df.copy()
        self.data.dropna(1,inplace=True)
        #LinearRegression doesn't use inf,NaN self\.datas. Flow Packets/s includes that so reduce it.
        self.data=self.data.drop(columns=[' Flow Packets/s'], axis=1, inplace=False)
        
    #make function to measure the mean
    def testing_all(self):
        x = self.data[self.data.columns[0:-1]]
        y = self.data[[' Label']]
        x_train,x_test,y_train,y_test = train_test_split(x,y,train_size=0.8,test_size=0.2)
        attack = ['DDoS', 'PortScan', 'Bot', 'Infiltration', 'Web Attack � Brute Force', 'Web Attack � XSS', 'Web Attack � Sql Injection']
        normal = 'BENIGN'
        y_train=y_train.replace(attack,-1)
        y_train=y_train.replace(normal,1)
        y_test=y_test.replace(attack,-1)
        y_test=y_test.replace(normal,1)
        model=GaussianNB()
        model.fit(x_train, y_train) 
        y_pred = model.predict(x_test)
        #Relabel values within a certain range to measure values
        for i in range(0,y_pred.size):
            if(y_pred[i]>0):
                y_pred[i]=1
            else:
                y_pred[i]=-1
        cf_matrix = confusion_matrix(y_test, y_pred)
        tn, fp, fn, tp = cf_matrix.ravel()
        recall = tp/(tp+fn)
        precision = tp/(tp+fp)
        print("Recall", recall, "\nPrecision", precision)
        f = 2 * (precision*recall)/(precision+recall)
        print("F1 Score", f)
        return f
        
    def get_result(self):
        sum=0
        for z in range(1,11):
            a = self.testing_all(self.data)
            sum +=a
        avg= sum / 10
        print("average f1 score:",avg)
        return("average f1 score:",avg)
