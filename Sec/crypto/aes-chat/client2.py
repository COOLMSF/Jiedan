# -*- coding: utf-8 -*-

import time
import encrypt
import configparser
import socket, threading
import numpy as np

# des测试函数
def string_to_bit_array(text):
    array = list()
    for char in text:
        binval = binvalue(char, 8)
        array.extend([int(x) for x in list(binval)])
    return array

def binvalue(val, bitsize): #Return the binary value as a string of the given size
    binval = bin(val)[2:] if isinstance(val, int) else bin(ord(val))[2:]
    if len(binval) > bitsize:
        raise "binary value larger than the expected size"
    while len(binval) < bitsize:
        binval = "0"+binval #Add as many 0 as needed to get the wanted size
    return binval

def bit_array_to_string(array):
    res = ''.join([chr(int(y,2)) for y in [''.join([str(x) for x in _bytes]) for _bytes in  nsplit(array,8)]])
    return res

IS_CHATTING = False
PORT_ANOTHER = 4000
AES_KEY = ''

def get_cfg():
    config = configparser.ConfigParser()
    config.read('client2.cfg', encoding='utf-8')
    port = config.get('config','port')
    host = config.get('config', 'host')

    global AES_KEY
    AES_KEY = config.get('config', 'aes-key')

    return host, int(port)

# 监听接收线程
def chat_server(host ,port):
    print("正在监听%d端口" % port)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        conn, addr = s.accept()

        print("IP %s 已连接" % str(addr))
        
        global IS_CHATTING

        if not IS_CHATTING:
            threading.Thread(target=chat_client, args=(addr, PORT_ANOTHER), name='client').start()
        
        global AES_KEY

        while True:
            try:
                data = conn.recv(512)
                print('=======================')
                print('原始数据如下', str(addr), data)
                decrypt_data = encrypt.decrypt(AES_KEY, data, 'Server1Public.pem')
                print('解密数据如下:', decrypt_data)
                print('=======================')
                if not data:
                    break 
            except Exception as e:
                break
            
# 发送数据线程     
def chat_client(host, port):

    global IS_CHATTING
    IS_CHATTING = True

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(('127.0.0.1', int(PORT_ANOTHER)))
        while True:
            con = input()
            
            print('=======================')
            print('原始数据如下', con)
            encrypt_con = myencdecrypt_data = encrypt.encrypt(AES_KEY, con, 'Client2Private.pem')
            print('AES加密结果如下:', encrypt_con)
            if con == 'bye':
                print('')
                s.close()
                break
            s.sendall(encrypt_con.encode('utf-8'))
            print('=======================')
            

if __name__ == "__main__":

    HOST ,PORT = get_cfg()
    print(AES_KEY)

    threading.Thread(target=chat_server, args=(HOST, PORT), name='server').start()
    # time.sleep(3)
    # threading.Thread(target=chat_client, args=("127.0.0.1", 4000), name='chat_client').start() 
    
    choose = input("1:)发送数据\n2:)接受数据")

    # 选择拨号
    if choose == '1':
        to_host = input('输入主机IP:')
        threading.Thread(target=chat_client, args=(to_host, 4000), name='chat_client').start() 
    elif choose == '2':
        print('正在等待客户端连接...')
    else:
        print('输入有误')
