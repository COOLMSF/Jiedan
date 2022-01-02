# encoding:utf-8
import os
import shutil
import tkinter as tk
from tkinter import filedialog
'''复制文件'''
def copy(path):
    new_path=path
    new_path=new_path.replace(old_site,new_site)#将源目录更换为目标目录
    print(path+'--复制--'+new_path)                 #选择文件和文件夹的时候输出会有差别？？？？（待解决）
    if os.path.isfile(new_path):        #目标文件是否存在
        print('文件已存在')               #这里没有做更详细的考虑，增量算法留待之后补充
    else:
        dirname=os.path.dirname(new_path)#提取目标文件的目录
        if os.path.exists(dirname):      #如果目标文件目录存在
            shutil.copy(path,new_path)   #直接复制
        else:
            try:#否则
                os.makedirs(dirname)     #创建目录
                shutil.copy(path,new_path)
            except WindowsError:
                print('创建目录出差')

'''获取源文件地址'''
def fildir(filname):          #传入的文件地址分隔符用\\否则可能被当作转义字符出错
    if os.path.isdir(filname):
        paths = os.listdir(filname)  # 扫描目录，获取文件列表
        for path in paths:
            path = os.path.join(filname, path)
            if (os.path.isdir(path)):  # 如果是目录，继续递归
                fildir(path)
            else:
                copy(path)  # 如果是文件，调用复制函数
    else:copy(filname)

def test():
    select = tk.Tk()  # 创建选择目录窗口
    select.withdraw()  # 隐藏窗口
    old_site = filedialog.askdirectory()  # 返回选择源目录
    new_site = filedialog.askdirectory()  # 返回目标目录
    fildir(old_site)

test()
