import socket
import json
from pythonping import ping
from MyRSA import RSA
from MyAES import AES
import os


pub_key = [7187, 61467355717]
pri_key = [49535765019, 61467355717]
import struct

ip = "127.0.0.1"
port =8888
BUF_SIZE = 1024
ca_pub_key = [9491, 117605212259]#保留CA中心的公钥，用来模拟CA数字中心的签发
cip = "127.0.0.1"
cport = 9999


def send_data(socket, data):
    socket.send(struct.pack('L', len(data)))
    socket.send(data)



def recv_data(socket):
    buf = socket.recv(struct.calcsize('L'))
    # 接收端接受数据大小信息
    data_size = struct.unpack('L', buf)[0]

    gap_abs = data_size % BUF_SIZE
    count = data_size // BUF_SIZE
    recv_data = b''
    for i in range(count):
        data = socket.recv(BUF_SIZE)
        recv_data += data
    recv_data += socket.recv(gap_abs)
    return recv_data

def str2utf8(strdata):
    return bytes(strdata, encoding='utf-8')

def utf82str(data):
    return str(data, encoding='utf-8')

class Server():
    def __init__(self):

        self.rsa=RSA()
        self.aes=AES()
        listen_fd = socket.socket()
        try:
            listen_fd.bind(("0.0.0.0", port))
            listen_fd.listen(5)
            while True:
                sock_fd, addr = listen_fd.accept()
                print("Received request from {}".format(addr))

                try:
                    request = utf82str(recv_data(sock_fd))
                    print("request:",request)

                    my_info = "0xdeadbeef"
                    if (request == my_info):  # 进行ssl连接确认
                        self.MyConnect(sock_fd, my_info)
                    else:
                        request = request.split()  # 指令之间使用空白符分割
                        cmd = request[0]  # 指令第一个为指令类型
                        print("cmd:", cmd)

                        if cmd == "url":  # 判断当前需要执行的指令
                            url_add = request[1]  # 得到第二个参数
                            response = self.ping(url_add)
                        elif cmd == "hello":  # 如果是鉴权消息
                            print("hello recv in server")
                            pass
                        else:
                            response = "Undefined command: " + " ".join(request)
                        send_data(sock_fd, str2utf8(response))
                        # sock_fd.send(bytes(response, encoding='utf-8'))
                except KeyboardInterrupt:
                    break
                finally:
                    sock_fd.close()
        except KeyboardInterrupt:
            pass
        except Exception as e:
            print(e)
        finally:
            listen_fd.close()


    def ping(self,url):
        message = ping(url)
        print(message)
        return  message
        '''
             success_ping = "Reply"
        if success_ping in str(message):
            return "ping " + url +" Success."
        else:
            return "ping " + url +" Fail."
        '''




    def get_ca(self):
        data={"ip":ip, "port":port, "pub_key":pub_key}
        data=json.dumps(data)

        ca_sock = socket.socket()
        ca_sock.connect((cip, cport))

        request = "ca"
        send_data(ca_sock, str2utf8(request))

        send_data(ca_sock, str2utf8(data))

        certi = utf82str(recv_data(ca_sock))
        ca_sock.close()

        return certi

    def MyConnect(self, sock_fd, my_info):
        print("server connection verification information success!")
        send_data(sock_fd, str2utf8("info status 200"))
        send_data(sock_fd, str2utf8(my_info))

        hello_msg = utf82str(recv_data(sock_fd)) #收到hello消息
        if(hello_msg != "hello"):
            sock_fd.close()
            return
        print("[1] recv  hello")

        ca = self.get_ca()
        signature = self.rsa.digi_signature(ca, pri_key)
        send_data(sock_fd, str2utf8(ca))  #向客户端直接发送CA证书
        send_data(sock_fd, str2utf8(str(signature))) #向客户端发送签名
        print("[2] Send CA")

        client_pubkey=self.decryRSA(sock_fd, pri_key) #目前还是字符串
        client_pubkey = self.str2arr(client_pubkey)
        print("[3] Get public key",client_pubkey)

        self.encryRSA(sock_fd, "Confirm client public key", client_pubkey)
        print("[*] Handshake complete!")

        encr_algor = self.decryRSA(sock_fd, pri_key).split(" ")
        self.aes_key=encr_algor[1]
        print("[4] algorithm:",encr_algor[0],",key：",encr_algor[1])

        info=encr_algor[0] +" confirm"
        self.encryRSA(sock_fd, info, client_pubkey)
        print("[5] SSL complete!")
        self.sh(sock_fd)

    def sh(self, sock):
        while True:
            try:
                request = utf82str(recv_data(sock))
                print("request:", request)

                my_info = "0xdeadbeef"
                if (request == my_info):
                    self.MyConnect(sock, my_info)
                else:
                    request = request
                    cmd = request.split()[0]

                    if cmd == "url":
                        url = request[3:]
                        url=self.str2arr(url)
                        url=self.aes.decode_des_to_str(url,len(url),self.aes_key)
                        print("parsed url:",url)
                        response = str(self.ping(url))
                    elif cmd == "hello":
                        print("hello recv in server")
                        pass
                    else:
                        response = "Undefined command: " + " ".join(request)

                    encode_url_rep = self.aes.aes(response, self.aes_key)
                    send_data(sock, str2utf8(str(encode_url_rep)))
                        # sock_fd.send(bytes(response, encoding='utf-8'))
            except KeyboardInterrupt:
                sock.close()
                exit()



    def str2arr(self, arr):
        arr=arr.strip()
        arr = arr[1:-1].split(',')
        arr = list(map(int, arr))
        return arr

    def encryRSA(self, socket, info:str, key):
        encode = self.rsa.encode(str(info), key)
        send_data(socket, str2utf8(str(encode)))

    def decryRSA(self, socket, key):
        confirm_mess = utf82str(recv_data(socket))
        confirm_mess=self.str2arr(confirm_mess)
        confirm_mess = self.rsa.decode_to_str(confirm_mess, key)
        new_ca_str=""
        for i in confirm_mess:
            if(ord(i)!=0):
                new_ca_str = new_ca_str + i
        return new_ca_str

if __name__ == '__main__':
    server = Server()
