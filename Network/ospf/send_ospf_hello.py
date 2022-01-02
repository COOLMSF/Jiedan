import ipaddress
from scapy.all import *
from scapy.contrib.ospf import *

# eth_src=input("Ether src:").encode()
# eth_src = bytes(eth_src.strip())
# 
# eth_dst=input("Ether dst:").encode()
# eth_dst=bytes(eth_dst.strip())
# 
# ip_src=input("ip src:").encode()
# ip_src=bytes(ip_src.strip())
# print(len(ip_src))
# ip_dst=input("ip dst:").encode()
# ip_dst=bytes(ip_dst.strip())

eth_src=input("Ether src:")[0:18]
print(eth_src)
eth_dst=input("Ether dst:")[0:18]
print(eth_dst)
ip_src=input("ip src:")
ip_dst=input("ip dst:")


# print("\nPacket Info:")
# print("Ethernet layer")
# print("eth src:" + eth_src)
# print("eth dst:" + eth_dst)
# print("IP layer:")
# print("ip src:" + ip_src)
# print("ip dst:" + ip_dst)


packet = Ether(src=eth_src,dst=eth_dst)
packet = packet/IP(src=ip_src,dst=ip_dst)
packet = packet/OSPF_Hdr(src=ip_src)
packet/OSPF_Hello(router='172.17.2.2',backup='172.17.2.1')

# packet = Ether(src='00:06:28:b9:85:31',dst='01:00:5e:00:00:05')
# packet = packet/IP(src='172.17.2.2',dst='224.0.0.5')
# packet = packet/OSPF_Hdr(src='172.17.2.2')
# packet/OSPF_Hello(router='172.17.2.2',backup='172.17.2.1')
packet.show()
sendp(packet,iface='en0')
