import datetime
import json
import socket
import struct
from MyRSA import RSA
from MyAES import AES
pub_key = [5771, 216007252163]
pri_key = [150654067331, 216007252163]


ip = "127.0.0.1"
port = 8888
BUF_SIZE = 1024
ca_pub_key = [9491, 117605212259]
aes_key = "abcdefghijklmnop"

def send_data(sock, data):
    sock.send(struct.pack('L',len(data)))
    sock.send(data)

def recv_data(sock):
    buf = sock.recv(struct.calcsize('L'))
    data_size = struct.unpack('L', buf)[0]
    gap_abs = data_size % BUF_SIZE
    count = data_size // BUF_SIZE
    result = b''
    for i in range(count):
        data = sock.recv(BUF_SIZE)
        result += data
    result += sock.recv(gap_abs)
    return result
def str2utf8(data):
    return bytes(data, encoding='utf-8')
def utf82str(data):
    return str(data, encoding='utf-8')



class Client:
    def __init__(self):
        self.client_sock = socket.socket()
        self.client_sock.connect((ip, port))
        self.rsa = RSA()
        self.aes = AES()
        self.auth = False

    def brief_veri(self):
        my_info = "0xdeadbeef"
        send_data(self.client_sock, str2utf8(my_info))
        rsp1 = utf82str(recv_data(self.client_sock))
        rsp2 = utf82str(recv_data(self.client_sock))
        if rsp1.find("200") > -1 and rsp2 == my_info:
            print("client connection verification information success!")

    def veri_ca(self, ca):
        ca_str = str(self.rsa.decode_to_str(ca, ca_pub_key))
        new_ca_str = ""
        for i in ca_str:
            if (ord(i) != 0):
                new_ca_str = new_ca_str + i
        try:
            json_ca = json.loads(new_ca_str)
            return json_ca
        except ValueError:
            return None

    def check_json_ca(self, json_ca, signature, content):
        if (json_ca != None):
            print("CA certificate decoding information", json_ca)

            self.server_ip_ = json_ca['server_ip']
            self.server_pub_key_ = json_ca['server_pub_key']
            self.vaild_date_ = json_ca['vaild_date']

            today = datetime.date.today()
            today = str(today)

            if ip != self.server_ip_:
                print("server ip inconsistent")
                self.client_sock.close()
                exit()
            if today > self.vaild_date_:
                print("The effective data has passed")
                self.client_sock.close()
                exit()

            sign = self.rsa.veri_sign(content, signature, self.server_pub_key_)
            if (not sign):
                print("         Incorrect digital signature")
                self.client_sock.close()
                exit()
            print("         Certificate verification is correct!")

        else:
            print("     Certificate verification is incorrect!")
            self.client_sock.close()
            exit()

    def ssl_connect(self):
        self.brief_veri()

        print("[1] Send hello!")
        ca, signature = self.hello()
        ca = self.str_to_arr(ca)
        signature = self.str_to_arr(signature)

        print("[2] Recv CA!")
        json_ca = self.veri_ca(ca)

        self.check_json_ca(json_ca, signature, str(ca))

        print("[3] Send public key!")
        self.rsa_encode(self.client_sock, str(pub_key), self.server_pub_key_)

        new_ca_str = self.rsa_decode(self.client_sock, pri_key)

        if (new_ca_str == "Confirm client public key"):
            print("[4] Public key transmission successful!")
        else:
            print("[4] Public key transmission failed!")
            self.client_sock.close()
            exit()

        print("[5] Negotiate encryption algorithm!")
        request = "AES {}".format(aes_key)
        self.rsa_encode(self.client_sock,request,self.server_pub_key_)

        new_ca_str = self.rsa_decode(self.client_sock, pri_key)
        if new_ca_str == "AES confirm":
            print("[6] SSL Complete!")
            self.auth = True
        else:
            print("[6] No confirmation message received!")
            self.client_sock.close()
            exit()


    def hello(self):
        request = "hello"

        send_data(self.client_sock, str2utf8(request))
        ca = utf82str(recv_data(self.client_sock))
        signature = utf82str(recv_data(self.client_sock))
        return ca, signature

    def request_url(self, url):
        request = "url {}".format(url)
        send_data(self.client_sock, bytes(request, encoding='utf-8'))
        response = utf82str(recv_data(self.client_sock))

        response=self.str_to_arr(response)
        if(self.auth):
            response=self.aes.decode_des_to_str(response,len(response),aes_key)
        return response


    def send_url(self, url):
        if (self.auth):
            pass
        else:
            my_info = "0xdeadbeef"
            request = "hello {}".format(my_info)
            send_data(self.client_sock, str2utf8(request))

    def str_to_arr(self, arr):
        arr=arr.strip()
        arr = arr[1:-1].split(',')
        arr = list(map(int, arr))
        return arr



    def rsa_encode(self, socket, info: str, key):
        encode = self.rsa.encode(str(info), key)
        send_data(socket, str2utf8(str(encode)))

    def rsa_decode(self, socket, key):
        confirm_mess = utf82str(recv_data(socket))
        confirm_mess = self.str_to_arr(confirm_mess)
        confirm_mess = self.rsa.decode_to_str(confirm_mess, key)
        new_ca_str = ""
        for i in confirm_mess:
            if (ord(i) != 0):
                new_ca_str = new_ca_str + i
        return new_ca_str

    def go(self, ):
        if not self.auth:
            client.ssl_connect()
        while True:
            url =  input("Enter a URL:")
            aes_encode_url = self.aes.aes(url,aes_key)
            response = self.request_url(str(aes_encode_url))
            print("result：\n",response)




if __name__ == '__main__':
    client = Client()

    client.go()

