#coding=utf-8
import dpkt
import socket
import geoip2.database

def GetPcap(pcap):
    ret = []
    for timestamp,packet in pcap:
        try:
            eth = dpkt.ethernet.Ethernet(packet)
            ip = eth.data
            src = socket.inet_ntoa(ip.src)
            dst = socket.inet_ntoa(ip.dst)
            # print("[+] 源地址: %-16s --> 目标地址: %-16s"%(src,dst))
            ret.append(dst)
        except:
            pass
    return set(ret)

if __name__ == '__main__':
    fp = open('data.pcap','rb')
    pcap = dpkt.pcap.Reader(fp)
    addr = GetPcap(pcap)
    reader = geoip2.database.Reader("d://GeoLite2-City.mmdb")
    for item in addr:
        try:
            response = reader.city(item)
            print("IP地址: %-16s --> " %item,end="")
            print("网段: %-16s --> " %response.traits.network,end="")
            print("经度: %-10s 纬度: %-10s --> " %(response.location.latitude, response.location.longitude),end="")
            print("地区: {}".format(response.country.names["zh-CN"]),end="\n")
        except Exception:
            pass
