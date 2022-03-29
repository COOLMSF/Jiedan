import socket

from ethernet_parser import EthernetParser
from ip_header_parser import  IPHeaderParser
from tcp_header_parser import TCPHeaderParser
from udp_header_parser import UDPHeaderParser

ETHER_PACKETS = 0x0003
BUFFER_SIZE = 65536


def parsePacket():
    connection = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(ETHER_PACKETS))

    tcp_parser = TCPHeaderParser()
    udp_parser = UDPHeaderParser()
    ip_parser = IPHeaderParser(tcp_parser=tcp_parser, udp_parser=udp_parser)

    ethernet_parser = EthernetParser(ipv4_parser=ip_parser)

    while True:
        raw_data, addr = connection.recvfrom(BUFFER_SIZE)
        print(raw_data)
        ethernet_parser.parse_header(raw_data)

