#!/usr/bin/python3.7
# -*- coding: utf-8 -*-

"""
RED ：报错、错误信息、失败信息
GREEN ：成功、重要发现
YELLOW ：警告、重要提示
BLUE ：保留
PURPLE ：保留
CYAN ：次要提示
"""

import os

class Colors:
    RED = "\033[91m"
    GREEN = "\033[32m"
    YELLOW = "\033[93m"
    BLUE = "\033[94m"
    PURPLE = "\033[95m"
    CYAN = "\033[96m"
    END = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"
    bgGREEN = "\033[42m"

os.system('')

# 成功消息 绿色
def successPrint(msg):
    print(Colors.GREEN + "[+] " + Colors.END + msg)

# 提示消息 蓝色
def hintPrint(msg):
    pass

# 警告消息 黄色
def warningPrint(msg):
    pass

# 错误/失败消息 红色
def errorPrint(msg):
    print(Colors.RED + "[-] " + Colors.END + msg)

def bgGreenPrint(msg):
    print(Colors.bgGREEN + msg + Colors.END)
