import hashlib
import random
from MyTools import *

class RSA():
    def __init__(self):
         li = eratosthenes(fast_pow(10, 6))

         idx1 = random.randint(0, len(li) - 1)
         idx2 = random.randint(0, len(li) - 1)
         p = li[idx1]
         q = li[idx2]
         fai = (p - 1) * (q - 1)
         idx = random.randint(1000, 10000)
         e = -1
         while (True):
             if (gcd(idx, fai) == 1):
                 e = idx
                 break
             idx = idx + 1
         self.p=p
         self.q=q
         self.e=e

    def cal_n_bit(self,n):
        if(n<8):
            return 8
        b_len=math.ceil(math.log2(n))
        for i in range(b_len,b_len+9):
            if(i%8==0):
                return (i-8)
        return b_len-8

    def __gen_key(self):
        # print("p:",p,",q:",q,",e:",e)
        n=self.p*self.q
        fai=(self.p-1)*(self.q-1)
        if self.e<=1 or self.e>=fai:
            print("error e value,please input 1<e<fai")
            return
        if gcd(self.e,fai)!=1:
            print("e and fai should be coprime")
            return
        d=ext_euclid_inv(self.e,fai)
        return [[self.e,n],[d,n]]

    def get_key(self):
        return self.__gen_key()

    def encode_m(self,m,pub_key):
        return fast_pow_mod(m,pub_key[0],pub_key[1])

    def decode_c(self,c,pri_key):
        return fast_pow_mod(c,pri_key[0],pri_key[1])


    def str_to_num(self,str,arr_len):
        res=[]
        for i in range(0,len(str),arr_len):
            num=0
            for ch in str[i:i+arr_len]:
                num=(num<<8)|ord(ch)
            res.append(num)
        return res

    def num_to_str(self,arr,arr_len):
        res=""
        for val in arr:
            tmp=""
            for i in range(arr_len):
                asc_num=val&0xFF
                tmp=chr(asc_num)+tmp
                val=val>>8
            res=res+tmp
        return res

    def encode(self,m,pub_key):
        n=pub_key[1]
        # print("n:",n)
        char_len=self.cal_n_bit(n)//8
        # print("char_len:",char_len)
        arr=self.str_to_num(m,char_len)
        return [self.encode_m(i,pub_key) for i in arr]

    def decode(self,c,pri_key):
        return [self.decode_c(i,pri_key)for i in c]

    def decode_to_str(self,c,pri_key):
        data= self.decode(c,pri_key)
        n = pri_key[1]
        char_len = self.cal_n_bit(n) // 8

        return self.num_to_str(data, char_len)

    def digi_signature(self,content,pri_key):
        md5=hashlib.md5()
        md5.update(content.encode('utf-8'))
        digest= md5.hexdigest()

        print("digest:",digest)
        return self.encode(digest,pri_key)

    def veri_sign(self,content,arr,pub_key):
        md5=hashlib.md5()
        md5.update(content.encode('utf-8'))
        digest= md5.hexdigest()

        decode_str=self.decode_to_str(arr,pub_key)
        return digest==decode_str


if __name__ == '__main__':
    rsa=RSA()

