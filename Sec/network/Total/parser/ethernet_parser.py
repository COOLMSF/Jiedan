from packet_parser import *
from xml_writer import XMLWriter

class EthernetParser(PacketParser):
    IPV4_PROTOCOL = 8
    MAC_HEADER_LENGTH = 14

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.dest_mac = ''
        self.src_mac = ''
        self.eth_proto = 0

    def parse_header(self, raw_data):
        self.dest_mac, self.src_mac, self.eth_proto, data = self._ethernet_frame(raw_data)

        print('\nEthernet frame:')
        print('Destination: {}, Source: {}, Protocol: {}'.format(self.dest_mac, self.src_mac, self.eth_proto))

        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.save_ethernet_frame_header(self.dest_mac, self.src_mac, self.eth_proto)

        if self.eth_proto == self.IPV4_PROTOCOL:
            self.next_parsers['ipv4_parser'].parse_header(data)
        else:
            print('Parser of {} is not defined'.format(self.eth_proto))

    def get_parsed_data(self):
        return self.dest_mac, self.src_mac, self.eth_proto

    def _ethernet_frame(self, data):
        dest_mac, src_mac, proto = struct.unpack('! 6s 6s H', data[:self.MAC_HEADER_LENGTH])
        return self._get_mac_addr(dest_mac), self._get_mac_addr(src_mac), socket.htons(proto), data[self.MAC_HEADER_LENGTH:]

    def _get_mac_addr(self, bytes_addr):
        bytes_str = map('{:02x}'.format, bytes_addr)
        return ':'.join(bytes_str).upper()
