#coding=utf-8
import dpkt
import socket

def FindPcapWord(pcap,WordKey):
    for timestamp,packet in pcap:
        try:
            eth = dpkt.ethernet.Ethernet(packet)
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

def FindHivemind(pcap):
    for timestamp,packet in pcap:
        try:
            eth = dpkt.ethernet.Ethernet(packet)
            ip = eth.data
            tcp = ip.data
            src = socket.inet_ntoa(ip.src)
            dst = socket.inet_ntoa(ip.dst)
            sport = tcp.sport
            dport = tcp.dport
            # print("[+] 源地址: {}:{} --> 目标地址:{}:{}".format(src,sport,dst,dport))
            if dport == 80 and dst == "125.39.247.226":
                # 如果数据流中存在cmd等明文命令则说明可能存在后门
                if '[cmd]# ' in tcp.data.lower():
                    print("[+] {}:{}".format(dst,dport))
        except Exception:
            pass

def FindDDosAttack(pcap):
    pktCount = {}
    for timestamp,packet in pcap:
        try:
            eth = dpkt.ethernet.Ethernet(packet)
            ip = eth.data
            tcp = ip.data
            src = socket.inet_ntoa(ip.src)
            dst = socket.inet_ntoa(ip.dst)
            sport = tcp.sport
            # 累计判断各个src地址对目标地址80端口访问次数
            if dport == 80:
                stream = src + ":" + dst
                if pktCount.has_key(stream):
                    pktCount[stream] = pktCount[stream] + 1
                else:
                    pktCount[stream] = 1
        except Exception:
            pass
    for stream in pktCount:
        pktSent = pktCount[stream]
        # 如果超过设置的检测阈值500,则判断为DDOS攻击行为
        if pktSent > 500:
            src = stream.split(":")[0]
            dst = stream.split(":")[1]
            print("[+] 源地址: {} 攻击: {} 流量: {} pkts.".format(src,dst,str(pktSent)))


if __name__ == "__main__":
    fp = open("data.pcap","rb")
    pcap = dpkt.pcap.Reader(fp)
    FindPcapWord(pcap,"wang.zip")
