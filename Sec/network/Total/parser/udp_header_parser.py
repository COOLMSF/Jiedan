from packet_parser import *
from xml_writer import XMLWriter

class UDPHeaderParser(PacketParser):
    UDP_HEADER_LENGTH = 8

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def parse_header(self, data):
        src_port, dest_port, length = struct.unpack('! H H 2x H', data[:self.UDP_HEADER_LENGTH])

        print('UDP Segment: ')
        print('Source port: {}, Destination Port: {}, Length: {}'.format(src_port, dest_port, length))
        print('Data: {}'.format(data[self.UDP_HEADER_LENGTH:]))

        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.save_udp_header(src_port, dest_port, length, data[self.UDP_HEADER_LENGTH:])
        xml_writer.save_to_xml_file()
