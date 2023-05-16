import socket
import json
import datetime
import struct


from MyRSA import RSA
pub_key = [9491, 117605212259]
pri_key = [3283657811, 117605212259]

port = 9999
BUF_SIZE = 1024


def send_data(sock, data):
    sock.send(struct.pack('L', len(data)))
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
class CA():
    def __init__(self):
        listen_fd = socket.socket()
        try:
            listen_fd.bind(("0.0.0.0", port))
            print("ca bind: {}".format(port))
            listen_fd.listen(5)
            while True:
                sock_fd, addr = listen_fd.accept()
                print("Received request from {}".format(addr))
                try:
                    request = utf82str(recv_data(sock_fd))
                    print("request:",request)

                    request = request.split()
                    cmd = request[0]

                    if cmd == "ca":
                        self.get_ca(sock_fd)

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
    def get_ca(self,sock_fd):
        j_data = utf82str(recv_data(sock_fd))
        meg_data = json.loads(j_data)

        server_ip = meg_data['ip']
        server_pub_key = meg_data['pub_key']

        date = datetime.date(2024, 1, 1)
        date = str(date)

        certi_info = dict()
        certi_info['server_ip'] = server_ip
        certi_info['server_pub_key'] = server_pub_key
        certi_info['vaild_date'] = date
        j_certi_info = json.dumps(certi_info)

        rsa=RSA()
        encode = rsa.encode(j_certi_info, pri_key)
        encode=str(encode)

        print("CA:",encode)
        send_data(sock_fd, str2utf8(encode))


if __name__ == '__main__':
    ca= CA()
