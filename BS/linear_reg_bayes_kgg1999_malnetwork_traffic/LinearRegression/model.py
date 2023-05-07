import numpy as np 
import pandas as pd
import warnings

from sklearn.model_selection import train_test_split     #一个自带的库，它自带一个叫做分割的函数，因为数据集是一个整块，得把它按比例划分

import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import time

from sklearn.metrics import accuracy_score
from sklearn.linear_model import LinearRegression     #线性模型有很多种，线性回归是其中的一种，它的算法就是一个二次函数
from sklearn.metrics import confusion_matrix

import os

class LinearReg:     #定义一个名为LinearReg的类
    data = None
    
    def __init__(self, datasource):
        warnings.filterwarnings('ignore')
        pd.set_option('display.max_columns', None)
        pd.set_option('display.max_rows', None)
        
        cols = [' Destination Port', ' Flow Duration', ' Total Fwd Packets',     #定义列，就是标签
                ' Total Backward Packets', 'Total Length of Fwd Packets', ' Total Length of Bwd Packets', 
                ' Fwd Packet Length Max',' Fwd Packet Length Min', ' Fwd Packet Length Mean', 
                ' Fwd Packet Length Std', 'Bwd Packet Length Max', ' Bwd Packet Length Min', 
                ' Bwd Packet Length Mean', ' Bwd Packet Length Std', 'Flow Bytes/s', 
                ' Flow Packets/s', ' Flow IAT Mean', ' Flow IAT Std', ' Flow IAT Max', 
                ' Flow IAT Min', 'Fwd IAT Total', ' Fwd IAT Mean', ' Fwd IAT Std', ' Fwd IAT Max',
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
                ' Init_Win_bytes_backward', ' act_data_pkt_fwd',
                ' min_seg_size_forward', 'Active Mean', ' Active Std', ' Active Max',
                ' Active Min', 'Idle Mean', ' Idle Std', ' Idle Max', ' Idle Min',' Label']
        
        # df = pd.DataFrame()
        # for file in os.listdir(datasource):
        #     newfile = os.path.join(datasource, file)
        #     print("======================\n" + newfile)
        #     
        #     new_df = pd.read_csv(newfile, usecols=cols)
        #     
        #     pd.concat([df, new_df])
        
        #读取数据，read是读，文件是csv格式的，pd就是pandas
        df1=pd.read_csv(os.path.join(datasource, "Friday-WorkingHours-Afternoon-DDos.pcap_ISCX.csv"), usecols = cols)
        df2=pd.read_csv(os.path.join(datasource, "Friday-WorkingHours-Afternoon-PortScan.pcap_ISCX.csv"), usecols = cols)
        df3=pd.read_csv(os.path.join(datasource, "Friday-WorkingHours-Morning.pcap_ISCX.csv"), usecols = cols)
        df4=pd.read_csv(os.path.join(datasource, "Thursday-WorkingHours-Afternoon-Infilteration.pcap_ISCX.csv"), usecols = cols)
        df5=pd.read_csv(os.path.join(datasource, "Thursday-WorkingHours-Morning-WebAttacks.pcap_ISCX.csv"), usecols = cols)
        
        #因为有很多数据，所以将它们分别读完后加起来
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
        self.data=self.data.drop(columns=[' Flow Packets/s'], axis=1, inplace=False)     #简单的数据清洗
        
    #make function to measure the mean
    def testing_all(self):
        x = self.data[self.data.columns[0:-1]]     #先找到x，找到x通过train_test_split这个函数
        y = self.data[[' Label']]
        x_train,x_test,y_train,y_test = train_test_split(x,y,train_size=0.8,test_size=0.2)     #这里按0.8和0.2划分
        attack = ['DDoS', 'PortScan', 'Bot', 'Infiltration', 'Web Attack � Brute Force', 'Web Attack � XSS', 'Web Attack � Sql Injection']     #攻击的标签，attack就是不正常的
        normal = 'BENIGN'     #normal就是正常的
        #把attack（恶性）的换成-1，normal（良性）的换成1.便于数据处理
        y_train=y_train.replace(attack,-1)
        y_train=y_train.replace(normal,1)
        y_test=y_test.replace(attack,-1)
        y_test=y_test.replace(normal,1)
        model=LinearRegression()     #直接调用线性回归这个函数，model是库里自带的（sklearn）
        model.fit(x_train, y_train)      #拟合
        y_pred = model.predict(x_test)     #预测，直接调用predict这个函数
        #Relabel values within a certain range to measure values
        for i in range(0,y_pred.size):
            if(y_pred[i]>0):
                y_pred[i]=1
            else:
                y_pred[i]=-1
        cf_matrix = confusion_matrix(y_test, y_pred)     #得出混淆矩阵
        tn, fp, fn, tp = cf_matrix.ravel()
        recall = tp/(tp+fn)    #计算召回
        precision = tp/(tp+fp)     #计算精度
        print("Recall", recall, "\nPrecision", precision)
        f = 2 * (precision*recall)/(precision+recall)
        print("F1 Score", f)     #将其打印出来
        # print("Model score", model.score())
        return f
        
    def get_result(self):
        sum=0
        # for z in range(1,21):
        for z in range(1,11):     #调用1-11共十次
            a = self.testing_all()     #每次测试的结果
            sum +=a
        avg= sum / 10
        #最后输出分数和结果
        print("average f1 score:",avg)
        return("average f1 score:" + str(avg))
