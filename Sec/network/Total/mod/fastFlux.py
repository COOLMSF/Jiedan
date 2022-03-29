#coding=utf-8
from scapy.all import *
from IPy import IP as PYIP

# 检查数据包的IP层,提取出IP和TTL字段的值
def Get_TTL(pkt):
    try:
        if pkt.haslayer(IP):
            ip_src = pkt.getlayer(IP).src
            ip_sport = pkt.getlayer(IP).sport
            ip_dst = pkt.getlayer(IP).dst
            ip_dport = pkt.getlayer(IP).dport
            ip_ttl = str(pkt.ttl)
            print("[+] 源地址: %15s:%-5s --> 目标地址: %15s:%-5s --> TTL: %-5s"%(ip_src,ip_sport,ip_dst,ip_dport,ip_ttl))
    except Exception:
        pass
# 获取本机发送出去的DNS请求所对应的网站地址
def Get_DNSRR(pkt):
    if pkt.haslayer(DNSRR):
        rrname = pkt.getlayer(DNSRR).rrname
        rdata = pkt.getlayer(DNSRR).rdata
        ttl = pkt.getlayer(DNSRR).ttl
        print("[+] 域名: {} --> 别名: {} --> TTL: {}".format(rrname,rdata,ttl))

if __name__=="__main__":
    sniff(prn=Get_DNSRR,store=0)

