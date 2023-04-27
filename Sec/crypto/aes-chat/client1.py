# -*- coding: utf-8 -*-

import configparser
import socket, threading
import encrypt
import time
import numpy as np

P = [16, 7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26, 5, 18, 31, 10,
     2, 8, 24, 14, 32, 27, 3, 9,
     19, 13, 30, 6, 22, 11, 4, 25]

PI_1 = [40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25]

# 测试函数
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
PORT_ANOTHER = 5000
AES_KEY = ''

# 读取配置文件
def get_config():
    config = configparser.ConfigParser()
    config.read('client1.cfg', encoding='utf-8')
    port = config.get('config','port')
    host = config.get('config', 'host')

    global AES_KEY
    AES_KEY = config.get('config', 'aes-key')

    return host, int(port)

# 监听接收线程
def socket_server(host ,port):
    print("主机%s正在监听%d端口" % (host, port))
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        conn, addr = s.accept()

        print("主机%s已连接" % str(addr))
        global IS_CHATTING
        
        # 如果不在通话，那么就开始读取输入并且发送
        if not IS_CHATTING:
            threading.Thread(target=socket_client, args=(str(addr), PORT_ANOTHER), name='client').start()
        
        while True:
            try:
                data = conn.recv(512)
                print('=======================')
                print('原数据:', str(addr), data)
                decrypt_data = encrypt.decrypt(AES_KEY, data, 'Server2Public.pem')
                print('解密后的数据:', decrypt_data)
                print('=======================')
                if not data:
                    break 
            except Exception as e:
                break
            
# 发送数据线程     
def socket_client(host, port):

    global IS_CHATTING, AES_KEY
    IS_CHATTING = True

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((str(host), int(PORT_ANOTHER)))
        while True:
            con = input()
            
            print('=======================')
            print('原始数据:', con)
            # AES 加密的密钥，加密内容，自己用于签名的私钥
            encrypt_con = encrypt.encrypt(AES_KEY, con, 'Client1Private.pem')
            print('加密后:', encrypt_con)
            if con == 'bye':
                print('')
                s.close()
                break
            s.sendall(encrypt_con.encode('utf-8'))
            print('=======================')
            
if __name__ == "__main__":

    HOST ,PORT = get_config()
    print('aes key:', AES_KEY)

    threading.Thread(target=socket_server, args=(HOST, PORT), name='server').start()
    # time.sleep(3)
    # threading.Thread(target=chat_client, args=("127.0.0.1", 5000), name='client').start()

        
    choose = input("1:)发送数据\n2:)接受数据")
    # 选择拨号
    if choose == '1':
        to_host = input('输入主机IP:')
        # 这里为了本机测试，直接写成 5000
        # threading.Thread(target=chat_client, args=(to_host, 4000), name='chat_client').start() 
        threading.Thread(target=socket_client, args=(to_host, 5000), name='chat_client').start() 
    elif choose == '2':
        print('正在等待客户端连接...')
    else:
        print('输入有误')
