#coding=utf-8
import dpkt
import socket

def FindPcapWord(pcap,WordKey):
    for ts,buf in pcap:
        try:
            eth = dpkt.ethernet.Ethernet(buf)
            ip = eth.data
            src = socket.inet_ntoa(ip.src)
            dst = socket.inet_ntoa(ip.dst)
            tcp = ip.data
            http = dpkt.http.Request(tcp.data)
            if(http.method == "GET"):
                uri = http.uri.lower()
                if WordKey in uri:
                    print("[+] 源地址: {} --> 目标地址: {} 检索到URL中存在 {}".format(src,dst,uri))
        except Exception:
            pass

fp = open("D://aaa.pcap","rb")
pcap = dpkt.pcap.Reader(fp)
FindPcapWord(pcap,"wang.zip")
