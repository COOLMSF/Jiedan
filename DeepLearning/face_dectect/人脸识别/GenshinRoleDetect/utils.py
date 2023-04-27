import os
import random
from config import *
import json
import matplotlib.pyplot as plt
def get_data_list(target_path,train_path,test_path):
    # 存放所有类别信息
    all_class_images = 0
    #存放标签
    class_label = 0
    # 存储train.txt与test.txt内容
    train_list = []
    test_list =[]
    #存放所有类别信息
    class_detail = []
    class_dirs = os.listdir(target_path) # 图片类名文件夹
    for class_dir in class_dirs:
        #类别数量
        class_sum = 0
        # 测试集数量
        test_sum = 0
        #训练集数量
        train_sum =0
        #每个类别信息
        class_detail_list = {}
        path = target_path + class_dir #图片类名路径
        img_paths = os.listdir(path)
        for img_path in img_paths:
            name_path = path + '/' + img_path # 每张图片路径
            if class_sum % 10 == 0:
                test_sum +=1
                test_list.append(name_path +'\t%d' % class_label+'\n')
            else:
                train_sum +=1
                train_list.append(name_path +'\t%d' % class_label+'\n')
            # 类别数目
            class_sum +=1
            #所有类别图片
            all_class_images += 1
            
        class_detail_list['class_name'] = class_dir
        class_detail_list['class_label']=class_label
        class_detail_list['class_test_images']=test_sum
        class_detail_list['class_train_images']=train_sum
        class_detail.append(class_detail_list)

        #初始化标签
        train_parameters['label_dict'][str(class_dir)] = class_label
        #类别数目
        class_label+=1
 
    random.shuffle(test_list)
    with open(test_path,'a') as f:
        for test_image in test_list:
            f.write(test_image)
    
    random.shuffle(train_list)
    with open(train_path,'a') as f:
        for train_image in train_list:
            f.write(train_image)    
    
    # 用于说明的json文件信息
    readjson = {'all_class_name':target_path,
                'all_class_images': all_class_images,
                'class_detail': class_detail}
    jsons = json.dumps(readjson, sort_keys=True, indent=4, separators=(',', ': '))
    with open(train_parameters['readme_path'], 'w') as f:
        f.write(jsons)
    print('生成数据列表完成.')



# 参数变化的可视化
def draw_train_process(title, iters, costs, accs, label_cost, label_acc):
    plt.title(title, fontsize=24)
    plt.xlabel('iter', fontsize=20)
    plt.ylabel('cost/acc', fontsize=20)
    plt.plot(iters, costs, color='red', label=label_cost)
    plt.plot(iters, accs, color='green', label=label_acc)
    plt.legend()
    plt.grid()
    plt.show()

def draw_process(title, color, iters, data, label):
    plt.title(title, fontsize=24)
    plt.xlabel('iter', fontsize=20)
    plt.ylabel(label, fontsize=20)
    plt.plot(iters, data, color=color, label=label)
    plt.legend()
    plt.grid()
    plt.show()
