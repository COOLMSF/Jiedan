import paddle
import os
import paddle.fluid as fluid
from multiprocessing import cpu_count



def save_model(model_dir,predict,exe):
    if not os.path.exists(model_dir):
        os.makedirs(model_dir)
    fluid.io.save_inference_model(model_dir,['image'],[predict],exe)

def vgg_bn_drop(image, type_size):
    def conv_block(ipt, num_filter, groups, dropouts):
        return fluid.nets.img_conv_group(
            input=ipt,  # 具有[N，C，H，W]格式的输入图像
            pool_size=2,
            pool_stride=2,
            conv_num_filter=[num_filter] * groups,  # 过滤器个数
            conv_filter_size=3,  # 过滤器大小
            conv_act='relu',
            conv_with_batchnorm=True,  # 表示在 Conv2d Layer 之后是否使用 BatchNorm
            conv_batchnorm_drop_rate=dropouts,  # 表示 BatchNorm 之后的 Dropout Layer 的丢弃概率
            pool_type='max')  # 最大池化

    conv1 = conv_block(image, 64, 2, [0.0, 0])
    conv2 = conv_block(conv1, 128, 2, [0.0, 0])
    conv3 = conv_block(conv2, 256, 3, [0.0, 0.0, 0])
    conv4 = conv_block(conv3, 512, 3, [0.0, 0.0, 0])
    conv5 = conv_block(conv4, 512, 3, [0.0, 0.0, 0])

    drop = fluid.layers.dropout(x=conv5, dropout_prob=0.5)
    fc1 = fluid.layers.fc(input=drop, size=512, act=None)

    bn = fluid.layers.batch_norm(input=fc1, act='relu')
    drop2 = fluid.layers.dropout(x=bn, dropout_prob=0.0)
    fc2 = fluid.layers.fc(input=drop2, size=512, act=None)
    predict = fluid.layers.fc(input=fc2, size=type_size, act='softmax')
    return predict


def train_mapper(sample):
    '''
    param sample (路径，类型)
    return 图像的张量
    '''
    #img 图片路径,label类别
    img,label = sample
    #读取图片
    img = paddle.dataset.image.load_image(img)
    # 标准化 
    img = paddle.dataset.image.simple_transform(im = img,crop_size = 128,resize_size=128,is_color=True, is_train=True)
    # 归一化,统一转为百分数
    img = img.astype("float32") / 255.0
    return img,label

'''
    param train_list 训练集路径
    param buffer_size 读取数量

'''
def train_reader(train_list,buffer_size=1024):
    def reader():
        with open (train_list,"r") as f:
            for line in f.readlines():
                line = line.replace("\n","")
                img_path,lbl = line.split("\t")
                yield img_path,int(lbl)
    return paddle.reader.xmap_readers(train_mapper,reader,cpu_count(),buffer_size) 

def test_reader(test_list):
    with open (test_list,"r") as f:
        for line in f.readlines():
            line = line.replace("\n","")
            img_path,lbl = line.split("\t")
            yield img_path,int(lbl)