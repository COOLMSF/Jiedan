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
# 获取本机发送出去的DNS请求所对应的网站地址 IP --> URL
def Get_DNSRR(pkt):
    if pkt.haslayer(DNSRR):
        rrname = pkt.getlayer(DNSRR).rrname
        rdata = pkt.getlayer(DNSRR).rdata
        ttl = pkt.getlayer(DNSRR).ttl
        print("[+] 域名: {} --> 别名: {} --> TTL: {}".format(rrname,rdata,ttl))

# 获取本机发送出去的网址请求解析为IP URL --> IP
def Get_DNSQR(pkt):
    # 判断是否含有DNSRR且存在UDP端口53
    if pkt.haslayer(DNSRR) and pkt.getlayer(UDP).sport == 53:
        rcode = pkt.getlayer(DNS).rcode
        qname = pkt.getlayer(DNSQR).qname
        # 若rcode为3，则表示该域名不存在
        if rcode == 3:
            print("[-] 域名解析不存在")
        else:
            print("[+] 解析存在:" + str(qname))

if __name__=="__main__":
    sniff(prn=Get_DNSQR,store=0)

