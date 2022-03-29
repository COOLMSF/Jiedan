#coding=utf-8
# pip install python-geoip-geolite2
# github地址下载：https://github.com/maxmind/GeoIP2-python
# 离线数据库：https://www.maxmind.com/en/accounts/current/geoip/downloads
import dpkt
import socket
import geoip2.database
from optparse import OptionParser

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

def retKML(addr,longitude,latitude):
    kml = (
              '<Placemark>\n'
              '<name>%s</name>\n'
              '<Point>\n'
              '<coordinates>%6f,%6f</coordinates>\n'
              '</Point>\n'
              '</Placemark>\n'
          ) %(addr, longitude, latitude)
    return kml

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-p", "--pcap", dest="pcap_file", help="set -p *.pcap")
    parser.add_option("-d", "--mmdb", dest="mmdb_file", help="set -d *.mmdb")
    (options, args) = parser.parse_args()
    if options.pcap_file and options.mmdb_file:
        fp = open(options.pcap_file,'rb')
        pcap = dpkt.pcap.Reader(fp)
        addr = GetPcap(pcap)
        reader = geoip2.database.Reader(options.mmdb_file)

        kmlheader = '<?xml version="1.0" encoding="UTF-8"?>\
        \n<kml xmlns="http://www.opengis.net/kml/2.2">\n<Document>\n'
        with open("GoogleEarth.kml", "w") as f:
            f.write(kmlheader)
            f.close()

        for item in addr:
            try:
                response = reader.city(item)
                print("IP地址: %-16s --> " %item,end="")
                print("网段: %-16s --> " %response.traits.network,end="")
                print("经度: %-10s 纬度: %-10s --> " %(response.location.latitude, response.location.longitude),end="")
                print("地区: {}".format(response.country.names["zh-CN"]),end="\n")

                with open("GoogleEarth.kml","a+") as f:
                    f.write(retKML(item,response.location.latitude, response.location.longitude))
                    f.close()
            except Exception:
                pass

        kmlfooter = '</Document>\n</kml>\n'
        with open("GoogleEarth.kml", "a+") as f:
            f.write(kmlfooter)
            f.close()
    else:
        parser.print_help()
