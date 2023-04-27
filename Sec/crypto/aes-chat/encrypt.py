# -*- coding: utf-8 -*-
# 外部库，提供加密解密功能

import rsa
import random
import base64
from Crypto.Cipher import AES

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def multiplicative_inverse(e, phi):
    d = 0
    x1 = 0
    x2 = 1
    y1 = 1
    temp_phi = phi

    while e > 0:
        temp1 = temp_phi//e
        temp2 = temp_phi - temp1 * e
        temp_phi = e
        e = temp2

        x = x2 - temp1 * x1
        y = d - temp1 * y1

        x2 = x1
        x1 = x
        d = y1
        y1 = y

    if temp_phi == 1:
        return d + phi

def is_prime(num):
    if num == 2:
        return True
    if num < 2 or num % 2 == 0:
        return False
    for n in range(3, int(num**0.5)+2, 2):
        if num % n == 0:
            return False
    return True

def get_private_key(filename):
    '''
    本地加载私钥文件
    '''
    prikey = ''
    with open(filename, 'r') as f:
        prikey = rsa.PrivateKey.load_pkcs1(f.read().encode())
    
    return prikey

def get_public_key(filename):
    '''
    本地加载公钥文件
    '''
    pubkey = ''
    with open(filename, 'r')  as f:
        pubkey = rsa.PublicKey.load_pkcs1(f.read().encode())
    
    return pubkey

def generate_key(n, filename):
    '''
    生成密钥文件
    '''
    pub_key, pri_key= rsa.newkeys(n)

    pri_filename = str(filename) + '_pri.pem' # 私钥名称
    pub_filename = str(filename) + '_pub.pem' # 公钥名称

    with open(pri_filename, 'w+') as f:
        f.write(pri_key.save_pkcs1().decode())

    with open(pub_filename, 'w+') as f:
        f.write(pub_key.save_pkcs1().decode())

def test_load():
    """
    测试加载
    """
    prikey = ''
    pubkey = ''
    with open('./keys/chat1_pri.pem', 'r') as f:
        prikey = rsa.PrivateKey.load_pkcs1(f.read().encode())
    
    with open('./keys/chat1_pub.pem', 'r') as f:
        pubkey = rsa.PublicKey.load_pkcs1(f.read().encode())

    print(prikey)
    print(pubkey)

    message = 'hello'

    sign = rsa.sign(message.encode(), prikey, 'SHA-1')
    print(len(sign))
    print(sign)
    verify = rsa.verify(message.encode(), sign, pubkey)
    print(verify)
    


def generate_key_pair(p, q):
    if not (is_prime(p) and is_prime(q)):
        raise ValueError('Both numbers must be prime.')
    elif p == q:
        raise ValueError('p and q cannot be equal')
    # n = pq
    n = p * q

    # Phi is the totient of n
    phi = (p-1) * (q-1)

    # Choose an integer e such that e and phi(n) are coprime
    e = random.randrange(1, phi)

    # Use Euclid's Algorithm to verify that e and phi(n) are coprime
    g = gcd(e, phi)
    while g != 1:
        e = random.randrange(1, phi)
        g = gcd(e, phi)

    # Use Extended Euclid's Algorithm to generate the private key
    d = multiplicative_inverse(e, phi)

    # Return public and private key_pair
    # Public key is (e, n) and private key is (d, n)
    return ((e, n), (d, n))


def encrypt(pk, plaintext):
    # Unpack the key into it's components
    key, n = pk
    # Convert each letter in the plaintext to numbers based on the character using a^b mod m
    cipher = [pow(ord(char), key, n) for char in plaintext]
    # Return the array of bytes
    return cipher


def decrypt(pk, ciphertext):
    # Unpack the key into its components
    key, n = pk
    # Generate the plaintext based on the ciphertext and key using a^b mod m
    aux = [str(pow(char, key, n)) for char in ciphertext]
    # Return the array of bytes as a string
    plain = [chr(int(char2)) for char2 in aux]
    return ''.join(plain)

def test():
    '''
    测试
    '''
        # 生成密钥
    key = rsa.newkeys(1024) 

    # 得到公钥和私钥
    pri_key = key[1]    
    pub_key = key[0]
    print('private_key:',pri_key)
    print('public_key:',pub_key)

    text = 'hello'
    print('before RSA encrypt:', text)
    text = text.encode()

    # 加密
    encrypt_text = rsa.encrypt(text, pub_key)
    print('after RSA encrypt:', encrypt_text)

    # 解密
    decrypt_text = rsa.decrypt(encrypt_text, pri_key)
    text = decrypt_text.decode()
    print('after RSA decrypt:', text)

    # 签名
    text = 'hello'.encode('utf-8')
    signature = rsa.sign(text, pri_key, 'SHA-1')
    verification = rsa.verify(text ,signature, pub_key)
    print(verification)
    signature = [len(signature)-2]
    try: 
        verification = rsa.verify(text ,signature, pub_key)
    except Exception as e:
        print('Error:', e)
        print('oh no')
    
if __name__ == '__main__':
    # 用于测试
    # test()
    # 生成两个用户的公钥和私钥
    # generate_key(1024, 'chat1')
    # generate_key(1024, 'chat2')
    test_load()


def pkcs7padding(text):
    bs = AES.block_size # 16
    length = len(text)
    bytes_length = len(bytes(text, encoding='utf-8'))
    # utf-8 编码，英文 1 byte，中文 3 byte
    # padding_size = length if (bytes_length == length) else bytes_length
    # 需要填充的字符长度
    padding = 128 - bytes_length
    print('message length', bytes_length, 'padding length', padding)
    # 填充的字符
    padding_text = chr(padding) * padding
    return text + padding_text

def pkcs7unpadding(text):
    '''
    处理使用 pkcs7 填充过的数据
    '''
    length = len(text)
    unpadding = ord(text[length-1])
    return text[0:length-unpadding]

def encrypt(key, content, prikeyname):
    key_bytes = bytes(key, encoding='utf-8')
    iv = key_bytes
    ciper = AES.new(key_bytes, AES.MODE_CBC, iv)
    # AES 加密处理明文
    content_padding = pkcs7padding(content)
    
    my_pri_key = get_private_key(prikeyname)

    my_sign = rsa.sign(content_padding.encode(), my_pri_key, 'SHA-1')
    print('Have signed with', prikeyname)

    all_content = bytes(content_padding, encoding='utf-8') + my_sign

    # 加密
    # encrypt_bytes = ciper.encrypt(bytes(content_padding, encoding='utf-8'))
    encrypt_bytes = ciper.encrypt(all_content)
    # 重新编码
    result = str(base64.b64encode(encrypt_bytes), encoding='utf-8')
    return result

def decrypt(key, content, pubkeyname):
    '''
    解密
    '''
    key_bytes = bytes(key, encoding='utf-8')
    iv = key_bytes
    cipher = AES.new(key_bytes, AES.MODE_CBC, iv)
    # base64解码
    encrypt_bytes = base64.b64decode(content)
    # 解密
    decrypt_bytes = cipher.decrypt(encrypt_bytes)
    # 重新编码
    result = str(decrypt_bytes[:128], encoding='utf-8')

    # 验证签名
    pubkey = get_public_key(pubkeyname)
    
    his_sign = decrypt_bytes[128:256]
    
    verify = rsa.verify(bytes(result, encoding='utf-8'), decrypt_bytes[128:256], pubkey)
    print('Checking Sign......')
    if verify:
        print('Checking Sign Successfully: ', verify)
    else:
        print('Checking Failed!!!')

    # 去除填充内容
    result = pkcs7unpadding(result)
    return result

def get_key(n):
    '''
    生成密钥，n 为密钥的长度
    '''
    c_length = int(n)
    source = 'ABCDEFGHJKMNPQRSTWXYZabcdefhijkmnprstwxyz2345678'
    length = len(source)-1
    result = ''
    for i in range(c_length):
        result += source[random.randint(0, length)]
    return result

if __name__ == '__main__':
    # 生成密钥
    # aes_key = get_key(16)
    aes_key = 'GENjnwZR4p2M5saR'
    print('key:', aes_key)

    # 加密
    source_en = 'Hello!'
    encrypt_en = encrypt(aes_key, source_en, './keys/chat1_pri.pem')
    print('before encrypt:', source_en)
    print('after encrypt:', encrypt_en)

    # 解密
    decrypt_en = decrypt(aes_key, encrypt_en, './keys/chat1_pub.pem')
    print('after decrypt:',decrypt_en)
    print(decrypt_en == source_en)
    




