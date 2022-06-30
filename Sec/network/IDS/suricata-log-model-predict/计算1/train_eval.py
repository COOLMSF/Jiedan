from BP import *
from sklearn import preprocessing
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
import math
from matplotlib import font_manager
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号














if __name__ == '__main__':

    # window_size = 3
    # 训练集处理
    min_max_scaler = preprocessing.MinMaxScaler()
    data = [[int(ele.strip())] for ele in open('./RL.txt').readlines()[:1005]]
    data = min_max_scaler.fit_transform(data)
    data = [ele.tolist()[0] for ele in data]
    pat = []

    for index in range(0, len(data)):
    # 对样本编组
        try:
            pat.append(
                [
                    [data[index], data[index+1], data[index+2]], [data[index+3]]
                ]
            )
        except:
            continue

    # window_size = 3
    # 测试集处理
    data2 = [[int(ele.strip())] for ele in open('./RL.txt').readlines()[1005:1295]]
    data2 = min_max_scaler.fit_transform(data2)
    data2 = [ele.tolist()[0] for ele in data2]
    pat2 = []

    for index in range(0, len(data2)):
        try:
            pat2.append(
                [
                    [data2[index], data2[index+1], data2[index+2]], [data2[index+3]]
                ]
            )
        except:
            continue
    # input_size = 3 hidden_size=12, output_size=1
    # 其他参数  迭代5000轮  动量参数 0.002 学习率0.001 学习率太大容易局部最优 激活函数sigmoid
    n = NN(3, 12, 1)
    # 训练 顺便得到损失用于画图
    loss = n.train(pat)
    pred1 = n.test(pat)

    # 预测
    pred2 = n.test(pat2)
    # 反归一化
    pred1 = min_max_scaler.inverse_transform(pred1)
    train_test = [ele[1] for ele in pat]
    train_test = min_max_scaler.inverse_transform(train_test)
    true_train = [i for j in train_test for i in j]

    pred2 = min_max_scaler.inverse_transform(pred2)
    test_true = [ele[1] for ele in pat2]
    test_true = min_max_scaler.inverse_transform(test_true)
    true_test = [i for j in test_true for i in j]
    # 误差
    train_error =[]
    pred3 =[i for j in pred1 for i in j]
    for i in range(0, len(pred3)):
        train_error.append((pred3[i]-true_train[i])/max(true_train))
       # print(i, float(pred1[i]), float(true_train[i]), float(pred1[i])-float(true_train[i]), train_error[i])

    test_error =[]
    pred4 = [i for j in pred2 for i in j]
    for i in range(0, len(pred4)):
        test_error.append((pred4[i]-true_test[i])/max(true_test))

    # 画图

    # 训练曲线
    x = list(range(0, len(pred1)))
    plt.title('训练曲线')
    plt.xlabel('样本序号')
    plt.ylabel('态势值')
    plt.plot(x, true_train, label='真实值')
    plt.plot(x, pred3, label='预测值')
    plt.legend(['训练-真实', '训练-预测'])
    plt.show()

    # 训练误差曲线
    x = np.arange(len(pred1))
    plt.title('训练误差曲线')
    plt.xlabel('样本序号')
    plt.ylabel('误差')
    plt.plot(np.arange(0, len(pred1)), train_error)
    plt.show()

    # 测试曲线
    x = list(range(0, len(pred2)))
    plt.title('测试曲线')
    plt.xlabel('样本序号')
    plt.ylabel('态势值')
    plt.plot(x, true_test, label='真实值')
    plt.plot(x, pred4, label='预测值')
    plt.legend(['测试-真实', '测试-预测'])
    plt.show()

    # 测试误差曲线
    x = list(range(0, len(pred2)))
    plt.title('测试误差曲线')
    plt.xlabel('样本序号')
    plt.ylabel('误差')
    plt.plot(x, test_error, 'black')
    plt.show()

    # 计算
    Ed = 0
    sumEd_2 = 0
    for i in range(0, len(test_error)):
        Ed += math.fabs(test_error[i])
        sumEd_2 += test_error[i] **2
    Ed = Ed/len(test_error)
    Vd = sumEd_2/len(test_error) - Ed **2
    print('Ed, Vd =', Ed, ',', Vd)