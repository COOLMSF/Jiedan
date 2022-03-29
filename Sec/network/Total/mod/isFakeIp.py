#!/usr/bin/python
#coding=utf-8
from scapy.all import *
import time
import optparse
# 为避免IPy库中的IP类与Scapy库中的IP类冲突，重命名为IPTEST类
from IPy import IP as IPTEST

ttlValues = {}
THRESH = 5

# 检查数据包的IP层，提取出源IP和TTL字段的值
def testTTL(pkt):
    try:
        if pkt.haslayer(IP):
            ipsrc = pkt.getlayer(IP).src
            ttl = str(pkt.ttl)
            checkTTL(ipsrc, ttl)
    except:
        pass

def checkTTL(ipsrc, ttl):
    # 判断是否是内网私有地址
    if IPTEST(ipsrc).iptype() == 'PRIVATE':
        return

    # 判断是否出现过该源地址，若没有则构建一个发往源地址的ICMP包，并记录回应数据包中的TTL值
    if not ttlValues.has_key(ipsrc):
        pkt = sr1(IP(dst=ipsrc) / ICMP(), retry=0, timeout=1, verbose=0)
        ttlValues[ipsrc] = pkt.ttl

    # 若两个TTL值之差大于阈值，则认为是伪造的源地址
    if abs(int(ttl) - int(ttlValues[ipsrc])) > THRESH:
        print '\n[!] Detected Possible Spoofed Packet From: ' + ipsrc
        print '[!] TTL: ' + ttl + ', Actual TTL: ' + str(ttlValues[ipsrc])

def main():
    parser = optparse.OptionParser("[*]Usage python spoofDetect.py -i <interface> -t <thresh>")
    parser.add_option('-i', dest='iface', type='string', help='specify network interface')
    parser.add_option('-t', dest='thresh', type='int', help='specify threshold count ')
    (options, args) = parser.parse_args()
    if options.iface == None:
        conf.iface = 'eth0'
    else:
        conf.iface = options.iface
    if options.thresh != None:
        THRESH = options.thresh
    else:
        THRESH = 5
    sniff(prn=testTTL, store=0)
if __name__ == '__main__':
    main()

