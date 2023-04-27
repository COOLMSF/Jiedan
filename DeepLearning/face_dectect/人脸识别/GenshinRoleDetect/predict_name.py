from re import A
from PIL import Image
import json
import paddle
import paddle.fluid as fluid
import numpy as np
import sys
import time 
import matplotlib.pyplot as plt
from simplejson import load
paddle.enable_static()
from config import *
from vgg16 import test_reader

def load_img(path):
    img = paddle.dataset.image.load_and_transform(path,128,128,False).astype("float32")
    img = img / 255.0
    return img

def face_detect(img_path,label=None):
    place = fluid.CUDAPlace(0) # 指定CPU
    infer_exe = fluid.Executor(place)# 指定场所
    model_path = train_parameters['model_dir'] # 模型路径
    # 加载模型
    infer_prog,feed_names,fetch_targets = fluid.io.load_inference_model(model_path,infer_exe)
    
    # 设置识别的图片
    test_img = img_path
    infer_imgs = []
    infer_imgs.append(load_img(test_img))
    infer_imgs = np.array(infer_imgs) 
    
    # 执行预测
    params = {feed_names[0]:infer_imgs}
    result = infer_exe.run(infer_prog,feed=params,fetch_list=fetch_targets)
    
    # 取出概率最高的模型
    idx = np.argmax(result[0][0])
    data = load_json()
    name_dict ={}
    for class_detail in  data['class_detail']:
        name_dict[class_detail['class_name']] = class_detail['class_label'];

    # 将idx对应数字转换为字典中的字符串
    for k,v in name_dict.items():
        if idx == v:
            print("预测结果:",k,end='\t')
            if label != None:
                for r,v in name_dict.items():
                    if label == v:
                        print("真实结果:",r)
            return k

def load_json():
    with open(train_parameters['readme_path'], 'r',encoding='utf-8:') as f:
        return json.load(f) 

if __name__ == '__main__':
    for path,label in test_reader(train_parameters['test_path']):
        face_detect(path,label)


