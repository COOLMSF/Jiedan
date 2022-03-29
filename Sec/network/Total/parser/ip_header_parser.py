from packet_parser import *
from xml_writer import XMLWriter

class IPHeaderParser(PacketParser):
    TCP_PROTOCOL = 6
    UDP_PROTOCOL = 17
    IPV4_HEADER_LENGTH = 20
    VERSION_LENGTH_IN_BITS = 4
    TOTAL_LENGTH_FIELD_START_INDEX = 15

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def parse_header(self, data):
        (version, header_length, ttl, proto, src, target, data) = self._ipv4_packet(data)
        print('IPv4 Packet:')
        print('Version: {}, Header length: {}, TTL: {}'.format(version, header_length, ttl))
        print('Protocol: {}, Source: {}, Target: {}'.format(proto, src, target))

        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.save_ip_header(version, header_length, ttl, proto, src, target)

        if proto == self.TCP_PROTOCOL:  # TCP
            self.next_parsers['tcp_parser'].parse_header(data)
        elif proto == self.UDP_PROTOCOL:  # UDP
            self.next_parsers['udp_parser'].parse_header(data)

    def _ipv4_packet(self, data):
        version_header_length = data[0]
        version = version_header_length >> self.VERSION_LENGTH_IN_BITS
        header_length = (version_header_length & self.TOTAL_LENGTH_FIELD_START_INDEX) * self.VERSION_LENGTH_IN_BITS
        ttl, proto, src, target = struct.unpack('! 8x B B 2x 4s 4s', data[:self.IPV4_HEADER_LENGTH])
        return version, header_length, ttl, proto, self._ipv4(src), self._ipv4(target), data[header_length:]

    # Return properly formatted IPV4 address
    def _ipv4(self, addr):
        return '.'.join(map(str, addr))
