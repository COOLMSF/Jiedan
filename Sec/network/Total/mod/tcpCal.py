#coding=utf-8
from scapy.all import *

def calTSN(tgt):
    seqNum = 0
    preNum = 0
    diffSeq = 0
    # 重复4次操作
    for x in range(1,5):
        # 若不是第一次发送SYN包，则设置前一个序列号值为上一次SYN/ACK包的序列号值
        # 逻辑出现问题
        # if preNum != 0:
        if seqNum != 0:
            preNum = seqNum
        # 构造并发送TCP SYN包
        pkt = IP(dst=tgt) / TCP()
        ans = sr1(pkt, verbose=0)
        # 读取SYN/ACK包的TCP序列号
        seqNum = ans.getlayer(TCP).seq
        if preNum != 0:
            diffSeq = seqNum - preNum
            print "[*] preNum: %d  seqNum: %d" % (preNum, seqNum)
            print "[+] TCP Seq Difference: " + str(diffSeq)
            print
    return seqNum + diffSeq

tgt = "192.168.220.128"
seqNum = calTSN(tgt)
print "[+] Next TCP Sequence Number to ACK is: " + str(seqNum + 1)

