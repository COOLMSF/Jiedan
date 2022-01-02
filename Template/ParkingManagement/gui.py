# coding=utf-8
import tkinter.font as tkFont
import tkinter.messagebox
from tkinter import messagebox
import tkinter as tk
import time
import os

import pyodbc
class YezhuManagementSystem(object):
    def __init__(self):
        self.yezhu = []
        self.__menu()

    def __menu(self):
        print("-" * 30)
        print("| 1 添加业主     |")
        print("| 2 删除业主     |")
        print("| 3 修改业主       |")
        print("| 4 查询信息                 |")
        print("| 5 退出业主管理系统         |")
        print("-" * 30)

    def add_yezhu(self, newyezhu):
        print()

    def del_yezhu(self, yezhu):
        print()

    def select(self):
        print()

    def is_has(self, newid):
        for yezhu in self.yezhu:
            if yezhu.get_id() == newid:
                return yezhu
        return 0


class CheweiManagementSystem(object):
    def __init__(self):
        self.chewei = []
        self.__menu()

    def __menu(self):
        print("-" * 30)
        print("| 1 添加车位     |")
        print("| 2 删除车位     |")
        print("| 3 修改车位       |")
        print("| 4 查询车位                 |")
        print("| 5 退出业车位管理系统         |")
        print("-" * 30)

    def add_chewei(self, newchewei):
        print()
    def del_chewei(self, chewei):
        print()
    def select(self):
        print()

    def is_has(self, newid):
        for chewei in self.chewei:
            if chewei.get_id() == newid:
                return chewei
        return 0


class YezhuCheliangManagementSystem(object):
    def __init__(self):
        self.yezhucheliang = []
        self.__menu()

    def __menu(self):
        print("-" * 30)
        print("| 1 添加车辆     |")
        print("| 2 删除车辆     |")
        print("| 3 修改车辆       |")
        print("| 4 查询车辆                 |")
        print("| 5 退出业车位管理系统         |")
        print("-" * 30)

    def add_yezhucheliang(self, yezhucheliang):
        print()

    def del_yezhucheliang(self, yezhucheliang):
        print()

    def select(self):
        print()

    def is_has(self, newid):
        for chewei in self.yezhucheliang:
            if chewei.get_id() == newid:
                return chewei
        return 0


class ZhibanyuangongManagementSystem(object):
    def __init__(self):
        self.zhibanyuangong = []
        self.__menu()

    def __menu(self):
        print("-" * 30)
        print("| 1 添加员工     |")
        print("| 2 删除员工     |")
        print("| 3 修改员工       |")
        print("| 4 查询员工                 |")
        print("| 5 退出系统         |")
        print("-" * 30)

    def add_zhibanyuangong(self, zhibanyuangong):
        print()

    def del_zhibanyuangong(self, zhibanyuangong):
        print()

    def select(self):
        print()

    def is_has(self, newid):
        for yuangong in self.zhibanyuangong:
            if yuangong.get_id() == newid:
                return yuangong
        return 0



class Yezhu(object):
    def __init__(self, id, name, phone):
        self.id = id
        self.name = name
        self.phone = phone
        self.car_num = {}

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_phone(self):
        return self.phone

    def get_car_num(self):
        for i, j in self.car_num.items():
            print(" %s:%d" % (i, j)),
        print

    def add_car_num(self, course, score):
        self.car_num[course] = score

    def modify_info(self):
        n_name = input("请输入修改后的名字：")
        n_phone = input("请输入修改后的电话：")
        self.phone = n_phone
        self.name = n_name


class Chewei():
    def __init__(self, id, chewei):
        self.id = id
        self.chewei_num = {}

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_chewei_num(self):
        for i, j in self.chewei_num.items():
            print(" %s:%d" % (i, j)),
        print

    def add_chewei_num(self, course, score):
        self.car_num[course] = score

    print()


class Yezhucheliang():
    class Yezhu(object):
        def __init__(self, id, type, chepai_num):
            self.id = id
            self.type = type
            self.chepai_num = chepai_num
            # self.car_num = {}

        def get_id(self):
            return self.id

        def get_type(self):
            return self.type

        def get_chepain_num(self):
            return self.chepai_num

        def add_car_num(self, course, score):
            self.car_num[course] = score

        def modify_info(self):
            n_type = input("请输入修改后的类型：")
            n_chepai = input("请输入修改后的车牌：")
            self.type = n_type
            self.chepai_num = n_chepai

    print()


class Zhibanyuangong():
    class zhibanyuangong(object):
        def __init__(self, id, name, sex, phone):
            self.id = id
            self.name = name
            self.sex = sex
            self.phone = phone
            # self.car_num = {}

        def get_name(self):
            return self.name

        def get_sex(self):
            return self.sex

        def get_phone(self):
            return self.phone

        def modify_info(self):
            n_name = input("请输入修改后的姓名：")
            n_sex = input("请输入修改后的性别：")
            n_phone = input("请输入修改后的电话：")
            self.name = n_name
            self.sex = n_sex
            self.phone = n_phone

    print()


def menu():
    print("1. 业主信息维护系统")
    print("2. 车位信息维护系统")
    print("3. 业主车辆信息维护系统")
    print("4. 值班员工信息维护系统")


def menu_yezhu():
    print("1. 增加业主信息")
    print("2. 删除业主信息")
    print("3. 修改业主信息")
    print("4. 查询业主信息")
    print("5. 返回上层")


def menu_zhibanyuangong():
    print("1. 增加员工信息")
    print("2. 删除员工信息")
    print("3. 修改员工信息")
    print("4. 查询员工信息")
    print("5. 返回上层")


def menu_yezhucheliang():
    print("1. 增加业主车辆信息")
    print("2. 删除业主车辆信息")
    print("3. 修改业主车辆信息")
    print("4. 查询业主车辆信息")
    print("5. 返回上层")

def menu_chewei():
    print("1. 增加车位信息")
    print("2. 删除车位信息")
    print("3. 修改车位信息")
    print("4. 查询车位信息")
    print("5. 返回上层")



class LoginView():
    window = tk.Tk()

    def __init__(self):
        self.initializeUI()

    def initializeUI(self):
        # self.window.iconbitmap("./resource/icon/hunter.ico")
        self.window.title('车位管理系统平台登录')
        background_color="white"
        self.window.configure(background=background_color)
        #self.window.overrideredirect(True)
        # photo = tk.PhotoImage(file="./resource/images/hunter.png")
        label = tk.Label(width=32, bg=background_color)
        label.place(x=60,y=40)

        ft = tkFont.Font(family='Fixdsys', size=16, weight=tkFont.BOLD)
        tk.Label(self.window, text="车位管理系统",font=ft, bg=background_color).place(x=100,y=44)

        # photo = tk.PhotoImage(file="./resource/images/splitline.png")
        label = tk.Label()
        # label.image =photo
        label.place(x=0,y=90)

        # 标签 用户名密码 #F3F3F4
        entryBackGroundColor="#F3F3F4"
        userNameFont = tkFont.Font(family='Fixdsys', size=10)
        tk.Label(self.window, text='请输入用户名:',font=userNameFont, bg=background_color).place(x=20, y=150)
        userName = tk.StringVar()
        tk.Entry(self.window, highlightthickness=1,bg=entryBackGroundColor,textvariable =userName).place(x=20, y=180,width=320, height=30)
        passWordFont = tkFont.Font(family='Fixdsys', size=10)
        passWord = tk.StringVar() #
        tk.Label(self.window, text='请输入密码:',font=passWordFont, bg=background_color).place(x=20, y=220)
        tk.Entry(self.window, highlightthickness=1, bg=entryBackGroundColor,textvariable =passWord, show='*').place(x=20, y=250,width=320, height=30)
        remeberMeFont=tkFont.Font(family='Fixdsys', size=12)
        tk.Button(self.window, text='立即登录', font=('Fixdsys', 14, 'bold'), width=29,fg='white',bg="#0081FF",command=lambda :self.login(userName,passWord)).place(x=20, y=330)

        regester_info=tkFont.Font(family='Fixdsys', size=10)
        w = 370
        h = 480
        sw = self.window.winfo_screenwidth()
        # 得到屏幕宽度
        sh = self.window.winfo_screenheight()# 窗口宽高为100
        x = (sw - w) / 2
        y = (sh - h) / 2
        self.window.geometry("%dx%d+%d+%d" % (w, h, x, y))
        self.window.mainloop()
        pass
    def login(self,userName,passWord):
        errMessage=""
        if len(userName.get())==0:
            errMessage=errMessage+"用户名不能为空！\r"
        if len(passWord.get())==0:
            errMessage=errMessage+"密码不能为空！"
        if errMessage!="":
            messagebox.showinfo('提示', errMessage)
        print(passWord.get())
        if userName.get() == "admin" and passWord.get() == "123456":
            tkinter.messagebox.showinfo("成功", "登陆成功")
            self.window.destroy()
        else:
            tkinter.messagebox.showinfo("错误", "登陆失败,请重试")
        pass


if __name__ == "__main__":

    LoginView()
    menu()
    conn_info = 'DRIVER={SQL Server};DATABASE=%s;SERVER=%s;UID=%s;PWD=%s' % (
        '车位管理系统1', '127.0.0.1', 'sa', '1')
    con = pyodbc.connect(conn_info)
    cur = con.cursor()

    while True:
        choice = int(input("请输入操作序号："))
        if choice == 1:
            yezhu_management_system = YezhuManagementSystem()

            while True:
                menu_yezhu()
                choice = int(input("请输入操作序号："))

                if choice == 1:
                    id = input("请输入您的id：")
                    name = input("请输入您的姓名：")
                    phone = input("请输入电话：")

                    is_has = yezhu_management_system.is_has(id)
                    while is_has != 0:
                        id = input("已有该业主！请重新输入id：")
                        is_has = yezhu_management_system.is_has(id)

                    new_chezhu = Yezhu(id, name, phone)
                    yezhu_management_system.add_yezhu(new_chezhu)

                    # db_cmd = "insert into yezhu_table values (\" " + id + "\"" + "," + "\"" + name + "\"" + "," + "\"" + phone + "\")"
                    db_cmd = "insert into yezhu_table values ('%s', '%s', '%s')" % (id, name, phone)
                    cur.execute(db_cmd)
                    cur.commit()
                    print("添加成功")

                    # db_cmd1 = "select * from yezhu_table"
                    # res = cur.execute(db_cmd1)
                    # Do something with your result set, for example print out all the results:
                    # for r in res:
                    #    print(r)
                    # cur.execute(db_cmd)
                    # cur.commit()

                elif choice == 2:
                    id = input("请输入您要删除的业主的id：")
                    is_has = yezhu_management_system.is_has(id)
                    if is_has != 0:
                        db_cmd = "delete from yezhu_table where id = '%s'" % id
                        # yezhu_management_system.del_yezhu(is_has)
                        cur.execute(db_cmd)
                        cur.commit()
                        printf("删除成功")

                    elif is_has == 0:
                        print("没有该id！")

                # elif choice == 3:
                #     id = input("请输入您要修改的学生的学号：")
                #     is_has = yezhu_management_system.is_has(id)
                #     if is_has != 0:
                #         is_has.()
                #     elif is_has == 0:
                #         print("没有该学号的学生！")

                elif choice == 4:
                    id = input("请输入要查询的id：")
                    db_cmd = "select * from yezhu_table where id = '%s'" % id
                    #yezhu_management_system.select()
                    ret = cur.execute(db_cmd)

                    for i in ret:
                        print(i)
                    print("查询成功")

                elif choice == 5:
                    break

        if choice == 2:
            chewei_management_system = CheweiManagementSystem()
            while True:
                menu_chewei()
                choice = int(input("请输入操作序号："))

                if choice == 1:
                    id = input("请输入车位id：")
                    chepai = input("请输车牌：")
                    is_has = chewei_management_system.is_has(id)
                    if is_has != 0:
                        print("车位已存在")
                    elif is_has == 0:
                        # chewei_management_system.add_chewei(is_has)
                        db_cmd = "insert into chewei_table values ('%s', '%s')" % ( id, chepai)
                        cur.execute(db_cmd)
                        print("添加车位成功")

                    # chewei_management_system.add_chewei()
                elif choice == 2:
                    id = input("请输入要删除的id：")
                    is_has = chewei_management_system.is_has(id)
                    if is_has != 0:
                        # chewei_management_system.del_chewei(is_has)
                        db_cmd = "delete from chewei_table where id = '%s'" % id
                        cur.execute(db_cmd)
                        cur.commit()
                        print("删除车位成功")
                    elif is_has == 0:
                        print("没有该id的车位！")

                # elif choice == 3:
                #     id = input("请输入您要修改的车位的id：")
                #     is_has = chewei_management_system.is_has(id)

                elif choice == 4:
                    # chewei_management_system.select()
                    id = input("请输入要查询的id：")
                    db_cmd = "select * from chewei_table where id = '%s'" % id
                    ret = cur.execute(db_cmd)

                    for i in ret:
                        print(i)


        if choice == 3:
            menu_yezhucheliang()
            yezhuchelicheliang_management_system = YezhuCheliangManagementSystem()
            while True:
                menu_chewei()
                choice = int(input("请输入操作序号："))

                if choice == 1:
                    id = input("请输入车量id：")
                    chepai = input("请输车牌：")
                    is_has = yezhuchelicheliang_management_system.is_has(id)
                    if is_has != 0:
                        print("车位已存在")
                    elif is_has == 0:
                        # yezhuchelicheliang_management_system.add_yezhucheliang(is_has)
                        db_cmd = "insert into yezhucheliang_table values ('%s', '%s')" % (id, chepai)
                        cur.execute(db_cmd)
                        cur.commit()
                        print("插入数据成功")

                    yezhuchelicheliang_management_system.add_yezhucheliang()
                elif choice == 2:
                    id = input("请输入要删除的id：")
                    is_has = yezhuchelicheliang_management_system.is_has(id)
                    if is_has != 0:
                        # yezhuchelicheliang_management_system.del_yezhucheliang(is_has)
                        db_cmd = "delete from yezhucheliang_table where id = '%s'" % id
                        cur.execute(db_cmd)
                        cur.commit()
                        print("删除车辆成功")

                    elif is_has == 0:
                        print("没有该id的车位！")

                # elif choice == 3:
                #     id = input("请输入您要修改的车位的id：")
                #     is_has = chewei_management_system.is_has(id)

                if choice == 4:
                    # yezhuchelicheliang_management_system.select()
                    id = input("请输入要查询的id：")
                    db_cmd = "select * from chewei_table where id = '%s'" % id
                    ret = cur.execute(db_cmd)
                    for i in ret:
                        print(i)


        if choice == 4:
            menu_zhibanyuangong()
            zhibanyuangong_management_system = ZhibanyuangongManagementSystem()
            while True:
                menu_zhibanyuangong()
                choice = int(input("请输入操作序号："))

                if choice == 1:
                    id = input("请输入员工id：")
                    sex = input("请输性别：")
                    phone = input("请输入电话：")
                    is_has = zhibanyuangong_management_system.is_has(id)
                    if is_has != 0:
                        print("员工已存在")
                    elif is_has == 0:
                        # zhibanyuangong_management_system.add_zhibanyuangong(is_has)
                        db_cmd = "insert into zhibanyuangong values ('%s', '%s', '%s')" % (id, sex, phone)
                        cur.execute(db_cmd)
                        cur.commit()
                        print("插入成功")
                    zhibanyuangong_management_system.add_zhibanyuangong()
                elif choice == 2:
                    id = input("请输入要删除的id：")
                    is_has = zhibanyuangong_management_system.is_has(id)
                    if is_has != 0:
                        # zhibanyuangong_management_system.del_zhibanyuangong(is_has)
                        db_cmd = "delete from zhibanyuangong_table where id = '%s'" % id
                        cur.execute(db_cmd)
                        cur.commit()
                        print("删除成功")

                    elif is_has == 0:
                        print("没有该id的员工！")

                # elif choice == 3:
                #     id = input("请输入您要修改的车位的id：")
                #     is_has = chewei_management_system.is_has(id)

                elif choice == 4:
                    id = input("请输入要查询的id：")
                    db_cmd = "select * from whre id = '%s'" % id
                    ret = cur.execute(db_cmd)
                    for i in ret:
                        print(i)
                    # zhibanyuangong_management_system.select()

        menu()
