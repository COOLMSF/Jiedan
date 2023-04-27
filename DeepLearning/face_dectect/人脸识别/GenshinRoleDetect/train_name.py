import json
import os
from tkinter import W
import paddle
import paddle.fluid as fluid
import numpy as np
import sys
from sklearn.feature_extraction import image
from vgg16 import *
from config import *
from utils import *

paddle.enable_static()

target_path = train_parameters['target_path']
model_dir = train_parameters['model_dir']
train_path = train_parameters['train_path']
test_path =  train_parameters['test_path']
    
with open(train_path, 'w') as f:
    f.seek(0)       # 游标移至文件头
    f.truncate()    # 截断游标后的字符
with open(test_path, 'w') as ff:
    ff.seek(0)
    ff.truncate()
# 划分数据集
get_data_list(target_path,train_path,test_path)

print(train_parameters['label_dict'])

#读取数据到train_reader
train_reader = train_reader(train_path)
# 打乱数据
random_train_reader = paddle.reader.shuffle(train_reader,buf_size=1300)
# 批量读取
batch_train_reader = paddle.batch(random_train_reader,batch_size=train_parameters['train_batch_size'])

# 占位符
image = fluid.layers.data(name='image',shape=[3,128,128],dtype="float32")
label = fluid.layers.data(name='label',shape=[1],dtype="int64")

# 调用函数
predict = vgg_bn_drop(image,3)
cost = fluid.layers.cross_entropy(input=predict,label=label)

#损失函数均值化
avg_cost  = fluid.layers.mean(cost) 

#优化器
optimizer = fluid.optimizer.Adam(learning_rate=train_parameters['learning_strategy']['lr'])
optimizer.minimize(avg_cost)

#计算准确率
accuracy =  fluid.layers.accuracy(input=predict,label=label)
#执行器
place = fluid.CUDAPlace(0)
exe = fluid.Executor(place)
exe.run(fluid.default_startup_program())

#喂入数据
feeder = fluid.DataFeeder(place=place,feed_list=[image,label])

all_train_iter = 0
all_train_iters = []
all_train_costs = []      # 代价列表
all_train_accs = []       # 准确率列表

# 开始训练
for epoch in range(train_parameters['num_epochs']):
    for bat_id,data in enumerate(batch_train_reader()):
        train_cost,train_acc = exe.run(fluid.default_main_program(),feed=feeder.feed(data),fetch_list=[avg_cost,accuracy])
        if bat_id % 20 == 0:
            
            print("epoch:%d,cost:%f,acc:%f" % (epoch,train_cost[0],train_acc[0]))
            all_train_iter = all_train_iter + train_parameters["train_batch_size"]
            all_train_iters.append(all_train_iter)
            all_train_costs.append(train_cost)
            all_train_accs.append(train_acc)


# 调用参数可视化函数进行参数可视化
draw_train_process('training', all_train_iters, all_train_costs, all_train_accs, 'training cost', 'traing_acc')
draw_process('training loss', 'red', all_train_iters, all_train_costs, 'training loss')
draw_process('training acc', 'green', all_train_iters, all_train_accs, 'training acc')


save_model(model_dir,predict,exe)