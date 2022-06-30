#!/usr/bin/env python
# -*- coding: utf-8 -*-

from wsgiref.handlers import format_date_time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
import string as ad


def cal(excel_filename):
    print("Start to work....")

    csv_filename = excel_filename.split('.')[0] + ".csv"
    result_filename = excel_filename.split('.')[0] + ".txt"

    result_fd = open(result_filename, 'w')
    df = pd.read_excel(excel_filename)
    df.to_csv(csv_filename, index=False,columns= [ 'time' , 'event', 'bandwidth'],  date_format="%Y/%m/%d %H:%M")
    # df = pd.read_excel("./h1-http.xlsx")
    # strip second
    df['time'] = df['time'].dt.floor('T')
    cc = pd.crosstab(df['time'], df['event'])
    cc.to_csv('temp_corsstab.csv', date_format="%Y/%m/%d %H:%M")

    # open csv file
    f_csv = open(csv_filename, "r")
    # skip the first line, because this line is title
    f_csv.readline()

    # define dic
    cnt_dic = {}
    bandwidth_dic = {}
    total_dic = {}

    # read data
    lines = f_csv.readlines()

    # init values to 0
    for line in lines:
        a = line.split(',')[0]
        t0 = a.split(' ')[0]
        t1 = a.split(' ')[1]
        if len(t1) < 5:
            t1 = '0' + t1
            
        # 2022/0/9
        date = t0.split(' ')[0]
        date0 = date.split('/')[0]
        date1 = date.split('/')[1]
        if len(date1) < 2:
            date1 = '0' + date1
        date2 = date.split('/')[2]

        if len(date2) < 2:
            date2 = '0' + date2

        a = date0 + '/' +  date1 + '/' + date2 + ' ' + t1




        b = line.split(',')[-3]


        cnt_dic[a] = 0
        bandwidth_dic[a] = 0
        total_dic[a] = {}

    # star to calculate
    for line in lines:
        # a is time
        a = line.split(',')[0]
        t0 = a.split(' ')[0]
        t1 = a.split(' ')[1]
        if len(t1) < 5:
            t1 = '0' + t1
            
        # 2022/0/9
        date = t0.split(' ')[0]
        date0 = date.split('/')[0]
        date1 = date.split('/')[1]
        if len(date1) < 2:
            date1 = '0' + date1
        date2 = date.split('/')[2]

        if len(date2) < 2:
            date2 = '0' + date2

        a = date0 + '/' + date1 + '/' + date2 + ' ' + t1

        # b is bandwidth
        b = line.split(',')[2]

        # a is like, which whill cause problem, 4/9 0:00
        # we should have time like this, 00:00
        # so prepend 0 before time

        # t0 = a.split(' ')[0]
        # t1 = a.split(' ')[1]
        # if len(t1) < 5:
        #     t1 = '0' + t1
        #     
        #     modified_time = t0 + ' ' + t1

        # a = modified_time

        # key found, just add b to it's value
        if bandwidth_dic[a] != 0:
            # sum bandwidth
            bandwidth_dic[a] = int(bandwidth_dic[a]) + int(b)
            # add counter
            cnt_dic[a] = cnt_dic[a] + 1

            total_dic[a] = { bandwidth_dic[a] : cnt_dic[a]}
        # no value found, assign b as value
        else:
            bandwidth_dic[a] = int(b)
            cnt_dic[a] = cnt_dic[a] + 1
            total_dic[a] = { bandwidth_dic[a] : cnt_dic[a]}

    # print(cnt_dic)
    # print(bandwidth_dic)

    # calculate average data
    for k, v in total_dic.items():
        for bandwidth, count in v.items():
            # print("bandwidth: " + str(bandwidth))
            # print("count: " + str(count))

            tmp = { int(bandwidth / count) : count }
            total_dic[k] = tmp

        #for bandwidth, count in total_dic[time]:
        #    print(bandwidth, count)


    f_corsstab = open("temp_corsstab.csv")

    # skip the first line
    f_corsstab.readline()
    crosstab_lines = f_corsstab.readlines()

    g = 0
    for line in crosstab_lines:

        tmp = line.split(',')
        time = tmp[0]
       # k0 = int(tmp[-4])
        k1 = int(tmp[-3])
        k2 = int(tmp[-2])
        k3 = int(tmp[-1])
        theta = 0
        
        a = total_dic
        for k, v in total_dic[time].items():
            f = k

        pd_time = pd.Timestamp(time)
        if (pd.Timestamp("02022-04-09 00:00:00") <= pd_time <= pd.Timestamp("02022-04-09 7:59:00")):
            theta = 0.321
        if (pd.Timestamp("02022-04-09 00:08:00") <= pd_time <= pd.Timestamp("02022-04-09 17:59:00")):
            if (pd.Timestamp("02022-04-09 13:00:00") <= pd_time <= pd.Timestamp("02022-04-09 13:20:00")):
                theta = 1
            else:
                 theta = 0.431
        else:
            if (pd.Timestamp("02022-04-09 22:00:00") <= pd_time <= pd.Timestamp("02022-04-09 22:20:00")):
                theta = 1
            else:
                theta = 0.248

        Rs = (k3 * 1000 + k2 * 100 + k1 * 10  + f * 100 ) *theta
        g += 1
        if(Rs == 0):
            break
        result_fd.writelines(str(int(Rs)) + '\n')

    result_fd.close()
    return (g)
    # print(total_dic)

def atoi(s):
    lenth = len(s)
    num = 0
    for i in s:
        lenth -= 1
        num = num + int(i) * (10 ** lenth)
    return(num)


 # 生成Rs
n1 = cal("h1-http.xlsx")
n2 = cal("h2-http.xlsx")
n3 = cal("h1-ssh.xlsx")
n4 = cal("h3-ssh.xlsx")
n5 = cal("h2-stmp.xlsx")
n6 = cal("h3-stmp.xlsx")
n = max(n1, n2, n3, n4, n5, n6)

Rs_h1_http =[0 for x in range(0,n)]
f1 = open("h1-http.txt")

for i in range(0,n):
    rs=f1.readline().rstrip('\n')
    Rs_h1_http[i] =atoi(rs)
f1.close()

Rs_h2_http =[0 for x in range(0,n)]
f1 = open("h2-http.txt")
for i in range(0,n):
    rs=f1.readline().rstrip('\n')
    Rs_h2_http[i] =atoi(rs)
f1.close()

Rs_h1_ssh =[0 for x in range(0,n)]
f1 = open("h1-ssh.txt")
for i in range(0,n):
    rs=f1.readline().rstrip('\n')
    Rs_h1_ssh[i] =atoi(rs)
f1.close()

Rs_h3_ssh =[0 for x in range(0,n)]
f1 = open("h3-ssh.txt")
for i in range(0,n):
    rs=f1.readline().rstrip('\n')
    Rs_h3_ssh[i] =atoi(rs)
f1.close()

Rs_h2_stmp =[0 for x in range(0,n)]
f1 = open("h2-stmp.txt")
for i in range(0,n):
    rs=f1.readline().rstrip('\n')
    Rs_h2_stmp[i] =atoi(rs)
f1.close()

Rs_h3_stmp =[0 for x in range(0,n)]
f1 = open("h3-stmp.txt")
for i in range(0,n):
    rs=f1.readline().rstrip('\n')
    Rs_h3_stmp[i] =atoi(rs)
f1.close()

#  生成Rh
Rh1 =[0 for x in range(0,n)]
Rh2 =[0 for x in range(0,n)]
Rh3 =[0 for x in range(0,n)]
fh1 = open("Rh1.txt", 'w')
fh2 = open("Rh2.txt", 'w')
fh3 = open("Rh3.txt", 'w')
fl = open("RL.txt", 'w')
for i in range(0,n):
    Rh1[i] = 0.526*Rs_h1_http[i] + 0.474*Rs_h1_ssh[i]
    fh1.writelines(str(int(Rh1[i])) + '\n')
    Rh2[i] = 0.769*Rs_h2_http[i] + 0.231*Rs_h2_stmp[i]
    fh2.writelines(str(int(Rh2[i])) + '\n')
    Rh3[i] = 0.667*Rs_h3_ssh[i] + 0.333*Rs_h3_stmp[i]
    fh3.writelines(str(int(Rh3[i])) + '\n')

# 生成RL
RL =[0 for x in range(0,n)]
for i in range(0,n):
    RL[i] = 0.431*Rh1[i] + 0.296*Rh2[i] + 0.273*Rh3[i]
    fl.writelines(str(int(RL[i])) + '\n')



fh1.close()
fh2.close()
fh3.close()
fl.close()

xs =[]
j = 0
for i in range(0, n):
    a = int(i/60)
    b = int(i%60)
    temp = str(a)+':'+str(b)
    xs.append(temp)


 # 绘制系统态势曲线
scale = np.arange(len(xs))
plt.figure(figsize=(30, 20), dpi=50)
plt.xticks(scale, xs, fontsize=13)
plt.yticks(fontsize=15)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(30))
plt.xlabel('时间', fontsize=25)
plt.ylabel('态势评估值', fontsize=25)
X = np.arange(0, n, 1)
Y = RL
plt.title('系统网络安全态势评估值', fontsize=30)
plt.plot(X, Y, 'b')

# 绘制h1-http态势曲线
plt.figure(figsize=(30, 20), dpi=50)
plt.xticks(scale, xs, fontsize=13)
plt.yticks(fontsize=15)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(30))
plt.xlabel('时间', fontsize=25)
plt.ylabel('态势评估值', fontsize=25)
Xs = np.arange(0, n1, 1)
Ys_h1_http = Rs_h1_http
plt.title('主机host1上http服务网络安全态势评估值', fontsize=30)
plt.plot(Xs, Ys_h1_http, 'b')

 # 绘制主机态势曲线

plt.figure(figsize=(30, 20), dpi=50)
plt.xticks(scale, xs, fontsize=13)
plt.yticks(fontsize=15)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(30))
plt.xlabel('时间', fontsize=25)
plt.ylabel('态势评估值', fontsize=25)
plt.title('主机host1网络安全态势评估值', fontsize=30)
X = np.arange(0, max(n1, n3), 1)
Y1 = Rh1
plt.plot(X, Y1, 'r')
plt.show()

plt.figure(figsize=(30, 20), dpi=50)
plt.xticks(scale, xs, fontsize=13)
plt.yticks(fontsize=15)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(30))
plt.xlabel('时间', fontsize=25)
plt.ylabel('态势评估值', fontsize=25)
plt.title('主机host2网络安全态势评估值', fontsize=30)
Y2 =[]
X = np.arange(0, max(n2, n5), 1)
for i in range(0, n):
    if (Rh2[i] > 0):
        Y2.append(Rh2[i])
    else:
        continue
plt.plot(X, Y2, 'black')
plt.show()

plt.figure(figsize=(30, 20), dpi=50)
plt.xticks(scale, xs, fontsize=13)
plt.yticks(fontsize=15)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(30))
plt.xlabel('时间', fontsize=25)
plt.ylabel('态势评估值', fontsize=25)
plt.title('主机host3网络安全态势评估值', fontsize=30)
Y3 =[]
X = np.arange(0, max(n4, n6), 1)
for i in range(0, n):
    if (Rh3[i] > 0):
        Y3.append(Rh3[i])
    else:
        continue
plt.plot(X, Y3, 'y')
plt.show()
