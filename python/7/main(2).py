# -*- coding:utf-8 -*-
import os
import shutil
import tkinter as tk
from tkinter import filedialog
from tkinter.constants import W

# 第1步，实例化object，建立窗口window
window = tk.Tk()
background_image = tk.PhotoImage("b.png")
window.configure(background="yellow")

# 第2步，给窗口的可视化起名字
window.title('My Window')

# 第3步，设定窗口的大小(长 * 宽)
window.geometry('600x200')  # 这里的乘是小x

# 放置两个静态文本
tk.Label(window,image=background_image,text='源文件', fg='white', bg="white", font=('宋体', 10), ).place(x=40, y=50, anchor='nw')
tk.Label(window,image=background_image,text='目标文件', fg='white', bg='red', font=('宋体', 10), ).place(x=40, y=80, anchor='nw')
#设置手动输入地址输入框
dress_y=tk.Entry(window,font=('宋体',10),width=40)
dress_y.place(x=120,y=52)
dress_m=tk.Entry(window,font=('宋体',10),width=40)
dress_m.place(x=120,y=82)

#设置按钮函数
def getdress(dress):
    dress.delete(0,'end')
    dress.insert(0,filedialog.askdirectory())

#设置复制函数
def act(old_site,new_site):
    '''复制文件'''
    def copy(path):
        new_path = path
        new_path = new_path.replace(old_site, new_site)  # 将源目录更换为目标目录
        if os.path.isfile(new_path):  # 目标文件是否存在
            print('文件已存在')  # 这里没有做更详细的考虑，增量算法留待之后补充
        else:
            dirname = os.path.dirname(new_path)  # 提取目标文件的目录
            if os.path.exists(dirname):  # 如果目标文件目录存在
                shutil.copy(path, new_path)  # 直接复制
                print(path + '--复制--' + new_path)  # 选择文件和文件夹的时候输出会有差别？？？？（待解决）
            else:
                try:  # 否则
                    os.makedirs(dirname)  # 创建目录
                    shutil.copy(path, new_path)
                    print(path + '--复制--' + new_path)  # 选择文件和文件夹的时候输出会有差别？？？？（待解决）
                except WindowsError:
                    print('创建目录出错')

    '''获取源文件地址'''
    def fildir(filname):  # 传入的文件地址分隔符用\\否则可能被当作转义字符出错
        if os.path.isdir(filname):
            paths = os.listdir(filname)  # 扫描目录，获取文件列表
            for path in paths:
                path = os.path.join(filname, path)
                if (os.path.isdir(path)):  # 如果是目录，继续递归
                    fildir(path)
                else:
                    copy(path)  # 如果是文件，调用复制函数
        else:
            copy(filname)

    fildir(old_site)

#设置按钮
tk.Button(window,text='浏览',command=lambda:getdress(dress_y)).place(x=410,y=48)
tk.Button(window,text='浏览',command=lambda:getdress(dress_m)).place(x=410,y=78)
tk.Button(window,text='复制',command=lambda:act(dress_y.get(),dress_m.get())).place(x=280,y=120)


# 第5步，主窗口循环显示
window.mainloop()
