from packet_parser import *
from xml_writer import XMLWriter

class TCPHeaderParser(PacketParser):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def parse_header(self, data):
        (src_port, dest_port, sequence, acknowledgement, offset_reserved_flags) = struct.unpack('! H H L L H', data[:14])
        offset = (offset_reserved_flags >> 12) * 4
        flag_urg = (offset_reserved_flags & 32) >> 5
        flag_ack = (offset_reserved_flags & 16) >> 4
        flag_psh = (offset_reserved_flags & 8) >> 3
        flag_rst = (offset_reserved_flags & 4) >> 2
        flag_syn = (offset_reserved_flags & 2) >> 1
        flag_fin = offset_reserved_flags & 1


        print('TCP Segment: ')
        print('Source port: {}, Destination Port: {}'.format(src_port, dest_port))
        print('Sequence: {}. AcknowledgementWITH_L: {}'.format(sequence, acknowledgement))
        print(self._format_multi_line('\t', data))
        print("".join(map(chr, data)))

        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.save_tcp_header(src_port, dest_port, sequence, acknowledgement, data)
        xml_writer.save_to_xml_file()

    def _format_multi_line(self, prefix, string, size=80):
        size -= len(prefix)
        if isinstance(string, bytes):
            string = ''.join(r'\x{:02x}'.format(byte) for byte in string)
            if size % 2:
                size -= 1
        return '\n'.join([prefix + line for line in textwrap.wrap(string, size)])
