import numpy as np

KEY = 'abcdefghijklmnop'

MIX_COLUMN_MATRIX = [[2, 3, 1, 1], [1, 2, 3, 1], [1, 1, 2, 3], [3, 1, 1, 2]]

INV_MIX_COLUMN_MATRIX = [[0xe, 0xb, 0xd, 0x9], [0x9, 0xe, 0xb, 0xd], [0xd, 0x9, 0xe, 0xb], [0xb, 0xd, 0x9, 0xe]]

RCON = [0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1B000000,
        0x36000000]

w_key = [None] * 44

SBOX = (
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16)

INV_SBOX = (
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D)

sbox = np.asarray(SBOX).reshape(16, 16)
inv_sbox = np.asarray(INV_SBOX).reshape(16, 16)

class AES():

    # 字节代换操作
    def sbox_query(self,data: int):
        line = data >> 4
        row = data & 0x0F
        # print(line)
        # print(row)
        return sbox[line][row]


    # arr是int[4][4],对整个数组进行字节代换
    def arr_sbox_replace(self,arr):
        for i in range(4):
            for j in range(4):
                arr[i][j] = self.sbox_query(arr[i][j])


    # arr是int[4][4],对整个数组进行字节代换
    def inv_arr_sbox_replace(self,arr):
        for i in range(4):
            for j in range(4):
                arr[i][j] = self.inv_sbox_query(arr[i][j])


    # 字节代换逆操作
    def inv_sbox_query(self,data: int):
        line = data >> 4
        row = data & 0x0F
        # print(line)
        # print(row)
        return inv_sbox[line][row]


    # 输入一个字符串，替换为其经过sbox
    def plaintext_sbox_query_transfer(self,plaintext: str):
        for i in range(len(input)):
            box_query = self.sbox_query(ord(input[i]))
            print('%#x' % box_query)


    # arr 是一个长度为4的int 数组，step是应该要移动的字节数
    def _left_shift_by_step(self,arr, step):
        step = step % 4;
        temp = np.array(arr)
        idx = step
        for i in range(len(arr)):
            arr[i] = temp[idx]
            idx = (idx + 1) % 4
        return arr


    # arr 是一个int[4][4]数组
    def shift_rows(self,arr):
        if (len(arr) != 4):
            print("请输入长度为4的二维数组")
            raise IOError
        arr = np.asarray(arr).reshape(4, 4)
        for i in range(1, 4):
            self._left_shift_by_step(arr[i], i)
        return arr


    # 行移位逆运算
    def _inv_left_shift_by_step(self,arr, step):
        step = step % 4;
        temp = np.array(arr)
        idx = step
        for i in range(len(arr)):
            arr[idx] = temp[i]
            idx = (idx + 1) % 4
        return arr


    # 行移位逆运算
    def inv_shift_rows(self,arr):
        if (len(arr) != 4):
            print("请输入长度为4的二维数组")
            raise IOError
        arr = np.asarray(arr).reshape(4, 4)
        for i in range(1, 4):
            self._inv_left_shift_by_step(arr[i], i)
        return arr


    # gf二元乘法
    def _gf_mul2(self,num: int):
        a7 = (num & 0x00000080) >> 7
        # print("a7",a7)
        if a7 == 1:
            res = ((num << 1) & 0x000000FF) ^ 0x1B
        else:
            res = ((num << 1) & 0x000000FF)
        return res


    def _gf_mul4(self,num: int):
        return self._gf_mul2(self._gf_mul2(num))


    def _gf_mul8(self,num: int):
        return self._gf_mul4(self._gf_mul2(num))


    def _gf_mul3(self,num: int):
        return self._gf_mul2(num) ^ num


    def _gf_mul9(self,num: int):
        return self._gf_mul8(num) ^ num


    def _gf_mulb(self,num: int):
        return self._gf_mul9(num) ^ self._gf_mul2(num)


    def _gf_muld(self,num: int):
        return self._gf_mul9(num) ^ self._gf_mul4(num)


    def _gf_mule(self,num: int):
        return self._gf_mul8(num) ^ self._gf_mul4(num) ^ self._gf_mul2(num)


    def gf_mul(self,n: int, mul=1):
        if mul == 1:
            return n;
        elif mul == 2:
            return self._gf_mul2(n)
        elif mul == 3:
            return self._gf_mul3(n)
        elif mul == 0x09:
            return self._gf_mul9(n)
        elif mul == 0x0b:
            return self._gf_mulb(n)
        elif mul == 0x0d:
            return self._gf_muld(n)
        elif mul == 0x0e:
            return self._gf_mule(n)
        return -1


    # 列混合运算
    def mix_column(self,matrix):
        matrix = np.asarray(matrix).reshape(4, 4)
        temp = np.array(matrix)

        for i in range(4):
            for j in range(4):
                matrix[i][j] = self.gf_mul(temp[0][j], MIX_COLUMN_MATRIX[i][0]) ^ self.gf_mul(temp[1][j],
                                                                                    MIX_COLUMN_MATRIX[i][1]) ^ self.gf_mul(
                    temp[2][j], MIX_COLUMN_MATRIX[i][2]) ^ self.gf_mul(temp[3][j], MIX_COLUMN_MATRIX[i][3])
        return matrix


    # 列混合逆运算
    def inv_mix_column(self,matrix):
        matrix = np.asarray(matrix).reshape(4, 4)
        temp = np.array(matrix)
        for i in range(4):
            for j in range(4):
                matrix[i][j] = self.gf_mul(temp[0][j], INV_MIX_COLUMN_MATRIX[i][0]) ^ self.gf_mul(temp[1][j],
                                                                                        INV_MIX_COLUMN_MATRIX[i][
                                                                                            1]) ^ self.gf_mul(temp[2][j],
                                                                                                         INV_MIX_COLUMN_MATRIX[
                                                                                                             i][
                                                                                                             2]) ^ self.gf_mul(
                    temp[3][j], INV_MIX_COLUMN_MATRIX[i][3])
        return matrix


    # 密钥扩展算法的t算法，key为一个int[4],turn 为当前轮次
    def _t_algo(self,key, turn):
        tmp = np.array(key)

        # 字节循环（左移1字节）
        shift_key = self._left_shift_by_step(tmp, 1)

        # Sbox字节代换
        sbox_shift_key = [self.sbox_query(data) for data in shift_key]

        # 与RCON做异或
        return [((RCON[turn] >> (24 - 8 * i)) & 0xff) ^ sbox_shift_key[i] for i in range(4)]



    # 密钥扩展算法，是一串字母，如raw_key='abcdefghijklmnop',必须是16个字母
    def round_key(self,raw_key):
        if (len(raw_key) != 16):
            print("密钥必须为16字节（128bit）,请输入正确的密钥！")
            raise TypeError
        for i in range(4):
            w_key[i] = [ord(j) for j in raw_key[i * 4:i * 4 + 4]]

        for i in range(4, 44):
            # 如果是4的倍数
            if (i % 4 == 0):
                turn = i // 4 - 1
                t_w = self._t_algo(w_key[i - 1], turn)
                w_key[i] = [w_key[i - 4][j] ^ t_w[j] for j in range(4)]
                # print("w_key[",i,"]=",end='')
                # print_hex(w_key[i])
            else:
                w_key[i] = [w_key[i - 4][j] ^ w_key[i - 1][j] for j in range(4)]
                # print("w_key[", i, "]=", end='')
                # print_hex(w_key[i])
        return w_key

    #arr1,arr2都是int[4][4]的数组，做异或，结果放到arr1里面
    def arr_xor(self,arr1,arr2):
        for i in range(4):
            for j in range(4):
                arr1[i][j]=arr1[i][j]^arr2[i][j]

    # x为明文，key为密钥,都是字符串形式，其中x的长度必须为16的倍数，key必须为16
    def aes(self,x, key):
        new_str=x
        x_len=len(x)
        while x_len%16!=0:
            new_str=new_str+" "
            x_len=x_len+1
        x=new_str

        if len(x) == 0 or len(x) % 16 != 0:
            # 暂时不支持填充字符
            print("明文字符的长度必须是16的倍数！")
            raise ValueError
        if len(key) != 16:
            # 目前只支持16字节(128bit)的密钥
            print("密钥字符长度必须为16！")
            raise ValueError

        # 密钥扩展
        self.round_key(key)

        res=[]

        for k in range(0, len(x), 16):
            # 将一个16个字符的明文转化为4*4的矩阵
            arr = self.str_to_int_array(x[k:k + 16])

            # print("arr after transfer:")
            # print_arr_hex(arr)

            # 轮密相加
            self.round_key_addition(arr, 0)

            # print("K中的第一轮")
            # print_arr_hex(arr,False)

            for i in range(1, 10):
                # print("*********第i=",i,"*********")
                # 字节代换
                self.arr_sbox_replace(arr)
                #
                # print("字节代换后")
                # print_arr_hex(arr)

                # 行移位
                arr = self.shift_rows(arr)
                #
                # print("行移位后")
                # print_arr_hex(arr)

                # 列混合
                self.mix_column(arr)
                #
                # print("列混合后")
                # print_arr_hex(arr)

                # 轮密相加
                self.round_key_addition(arr, i)
                #
                # print("轮密相加后")
                # print_arr_hex(arr)
                #
                # print("*********第i=",i,"结束*********")

            # 第10轮
            # 字节代换
            self.arr_sbox_replace(arr)
            # 行移位
            arr = self.shift_rows(arr)
            # 轮密相加
            self.round_key_addition(arr, 10)

            for i in range(4):
                for j in range(4):
                    res.append(arr[j][i])

        return res

    def get_arr_from_encode(self,encode,round):
        arr=[None]*4
        for i in range(4):
            arr[i]=[None]*4
        idx=round*16
        for i in range(4):
            arr[0][i] = encode[idx+i*4]
            arr[1][i] = encode[idx+i*4+1]
            arr[2][i] = encode[idx+i*4+2]
            arr[3][i] = encode[idx+i*4+3]
        return arr

    def decode_des_to_str(self,encode, length, key):
        res = self.decode_des(encode, len(encode), key)
        return self.intarr_to_str(res).strip()


    # 密文的arr 是一个int[4][4]格式,len为密文arr的长度，默认为16,key为密钥
    def decode_des(self,encode, length, key):
        if len(key) != 16:
            # 目前只支持16字节(128bit)的密钥
            print("密钥字符长度必须为16！")
            raise ValueError

        res=[]
        # 密钥扩展
        self.round_key(key)

        for k in range(0, length, 16):

            arr=self.get_arr_from_encode(encode,k//16)
            # 轮密相加
            self.round_key_addition(arr, 10)

            # print("经过第一个k")
            # print_arr_hex(arr, False)
            for i in range(9, 0, -1):
                # print("*********第i=",i,"*********")
                # 逆字节代换
                self.inv_arr_sbox_replace(arr)

                # print("逆字节代换后")
                # print_arr_hex(arr)

                # 逆行移位
                arr = self.inv_shift_rows(arr)

                # print("逆行移位后")
                # print_arr_hex(arr)

                # 逆列混合
                self.inv_mix_column(arr)

                # print("逆列混合后")
                # print_arr_hex(arr)

                w = self.get_arr_from_w(i)
                # print("得到的wArray为")
                # print_arr_hex(w)

                w=self.inv_mix_column(w)

                # print("得到列混合的wArray为")
                # print_arr_hex(w)

                self.arr_xor(arr,w)

                # print("二者做异或后：")
                # print_arr_hex(arr)
                # print("*********第i=",i,"结束*********")

            # 最后一轮，少了列混合
            # 逆字节代换
            self.inv_arr_sbox_replace(arr)

            # 逆行移位
            arr = self.inv_shift_rows(arr)

            # 轮密相加
            self.round_key_addition(arr, 0)

            for i in range(4):
                for j in range(4):
                    res.append(arr[j][i])
        return res


    # x为长度为16的字符串明文（如x="abcdefghijklmnop"），将其转化为4*4的数组
    def str_to_int_array(self,x):
        res = [None] * 4
        for i in range(4):
            res[i] = [ord(x[i + idx]) for idx in range(0, 13, 4)]
        return res


    # 轮密钥加,arr 就是 str_to_int_array 方法得到 int[4][4] 数组，round 就是第几轮
    def round_key_addition(self,arr, round):
        w0 = w_key[round * 4]
        w1 = w_key[round * 4 + 1]
        w2 = w_key[round * 4 + 2]
        w3 = w_key[round * 4 + 3]

        w = [w0, w1, w2, w3]

        for j in range(4):
            arr[0][j] = arr[0][j] ^ w[j][0]
            arr[1][j] = arr[1][j] ^ w[j][1]
            arr[2][j] = arr[2][j] ^ w[j][2]
            arr[3][j] = arr[3][j] ^ w[j][3]


    def get_arr_from_w(self,round):
        w0 = w_key[round * 4]
        w1 = w_key[round * 4 + 1]
        w2 = w_key[round * 4 + 2]
        w3 = w_key[round * 4 + 3]

        w = [None] * 4
        for i in range(4):
            w[i] = [None] * 4
            w[i][0] = w0[i]
            w[i][1] = w1[i]
            w[i][2] = w2[i]
            w[i][3] = w3[i]

        return w



    def print_hex(self,data):
        for i in data:
            print("%#x " % i, end='')
        # print()


    def print_arr_hex(self,arr, line=False):
        if line:
            for i in range(4):
                for j in range(4):
                    print("%#x " % arr[i][j], end='')
            print()
        else:
            for i in range(4):
                self.print_hex(arr[i])

    #arr是一个一维int[]数组
    def intarr_to_str(self,arr):
        return "".join(chr(i) for i in arr)

if __name__ == '__main__':
    aes= AES()

