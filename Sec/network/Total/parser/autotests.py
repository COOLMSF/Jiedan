import unittest
import os
from ethernet_parser import EthernetParser
from ip_header_parser import  IPHeaderParser
from tcp_header_parser import TCPHeaderParser
from udp_header_parser import UDPHeaderParser
from xml_reader import XMLReader
from xml_writer import XMLWriter

tcp_parser = TCPHeaderParser()
udp_parser = UDPHeaderParser()
ip_parser = IPHeaderParser(tcp_parser=tcp_parser, udp_parser=udp_parser)

ethernet_parser = EthernetParser(ipv4_parser=ip_parser)


class TestPacketParser(unittest.TestCase):

    def testTCPParserWithoutData(self):
        raw_data = b'\x6c\x71\xd9\x61\xf1\xa1\xc0\x4a\x00\x57\x00\xee\x08\x00\x45\x00\x00\x34\xd5\x74\x40\x00\x39\x06\xa3\x56\x97\x65\x70\x85\xc0\xa8\x00\x66\x01\xbb\x86\x2c\xa8\x7e\x90\xd2\xc8\x58\x1a\x83\x80\x10\x00\x3f\x95\xef\x00\x00\x01\x01\x08\x0a\xe7\x84\x79\xa2\xac\x4c\x66\x0d'
        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.setPath('testTCPParserWithoutData.xml')
        ethernet_parser.parse_header(raw_data)

        xml_reader = XMLReader('testTCPParserWithoutData.xml')
        dest, src, proto = xml_reader.get_ethernet_frame_header()

        self.assertEqual(dest, '6C:71:D9:61:F1:A1')
        self.assertEqual(src, 'C0:4A:00:57:00:EE')
        self.assertEqual(proto, '8')

        version, header_length, ttl, protocol, source, target = xml_reader.get_ip_header()
        self.assertEqual(version, '4')
        self.assertEqual(header_length, '20')
        self.assertEqual(ttl, '57')
        self.assertEqual(protocol, '6')
        self.assertEqual(source, '151.101.112.133')
        self.assertEqual(target, '192.168.0.102')

        source_port, destination_port, sequence, acknowledgement, data = xml_reader.get_tcp_header()
        self.assertEqual(source_port, '443')
        self.assertEqual(destination_port, '34348')
        self.assertEqual(sequence, '2826866898')
        self.assertEqual(acknowledgement, '3361217155')

        os.remove('testTCPParserWithoutData.xml')

    def testTCPParserWithData(self):
        print('testTCPParserWithData')
        raw_data = b'lq\xd9a\xf1\xa1\xc0J\x00W\x00\xee\x08\x00E\x00\x004\xb0\xd8@\x00V\x06\x00\xcc\x9d\xf0\x14#\xc0\xa8\x00d\x01\xbb\x80\xcc\xe9\x88\xd9\x84\xc3\x13@^\x80\x10\x00rV\xdc\x00\x00\x01\x01\x08\nWn\xaf1\xec6pq'
        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.setPath('testTCPParserWithData.xml')
        ethernet_parser.parse_header(raw_data)

        xml_reader = XMLReader('testTCPParserWithData.xml')
        dest, src, proto = xml_reader.get_ethernet_frame_header()

        self.assertEqual(dest, '6C:71:D9:61:F1:A1')
        self.assertEqual(src, 'C0:4A:00:57:00:EE')
        self.assertEqual(proto, '8')

        version, header_length, ttl, protocol, source, target = xml_reader.get_ip_header()
        self.assertEqual(version, '4')
        self.assertEqual(header_length, '20')
        self.assertEqual(ttl, '86')
        self.assertEqual(protocol, '6')
        self.assertEqual(source, '157.240.20.35')
        self.assertEqual(target, '192.168.0.100')

        source_port, destination_port, sequence, acknowledgement, data = xml_reader.get_tcp_header()
        self.assertEqual(source_port, '443')
        self.assertEqual(destination_port, '32972')
        self.assertEqual(sequence, '3918059908')
        self.assertEqual(acknowledgement, '3272818782')

        print('============= data in tests = ', data)
        #self.assertEqual(data, b'\x01\xbb\x80\xcc\xe9\x88\xd9\x84\xc3\x13@^\x80\x10\x00rV\xdc\x00\x00\x01\x01\x08\nWn\xaf1\xec6pq')
        os.remove('testTCPParserWithData.xml')

    def testParserUDPWithoutData(self):
        raw_data = b'\xc0J\x00W\x00\xeelq\xd9a\xf1\xa1\x08\x00E\x00\x00AQi@\x00@\x11g\x8d\xc0\xa8\x00d\xc0\xa8\x00\x01\xe2\x1e\x005\x00-\xcd@\x95\x87\x01\x00\x00\x01\x00\x00\x00\x00\x00\x00\x08clients1\x06google\x03com\x00\x00\x01\x00\x01'
        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.setPath('testParserUDPWithoutData.xml')
        ethernet_parser.parse_header(raw_data)

        xml_reader = XMLReader('testParserUDPWithoutData.xml')
        dest, src, proto = xml_reader.get_ethernet_frame_header()

        self.assertEqual(dest, 'C0:4A:00:57:00:EE')
        self.assertEqual(src, '6C:71:D9:61:F1:A1')
        self.assertEqual(proto, '8')

        version, header_length, ttl, protocol, source, target = xml_reader.get_ip_header()
        self.assertEqual(version, '4')
        self.assertEqual(header_length, '20')
        self.assertEqual(ttl, '64')
        self.assertEqual(protocol, '17')
        self.assertEqual(source, '192.168.0.100')
        self.assertEqual(target, '192.168.0.1')

        source_port, destination_port, length, data = xml_reader.get_udp_header()
        self.assertEqual(source_port, '57886')
        self.assertEqual(destination_port, '53')
        self.assertEqual(length, '52544')

       # os.remove('testParserUDPWithoutData.xml')

    def testParserUDPWithData(self):
        raw_data = b'\x01\x00^\x7f\xff\xfa\xc0J\x00W\x00\xee\x08\x00E\x00\x01-\x00\x00@\x00\x04\x11\xc5\x1c\xc0\xa8\x00\x01\xef\xff\xff\xfa\x80\x01\x07l\x01\x19f>NOTIFY * HTTP/1.1\r\nHOST: 239.255.255.250:1900\r\nCACHE-CONTROL: max-age=100\r\nLOCATION: http://192.168.0.1:1900/igd.xml\r\nNT: uuid:9f0865b3-f5da-4ad5-85b7-7404637fdf37\r\nNTS: ssdp:alive\r\nSERVER: ipos/7.0 UPnP/1.0 TL-WR840N/1.0\r\nUSN: uuid:9f0865b3-f5da-4ad5-85b7-7404637fdf37\r\n\r\n'
        xml_writer = XMLWriter.getXMLWriter()
        xml_writer.setPath('testParserUDPWithData.xml')
        ethernet_parser.parse_header(raw_data)

        xml_reader = XMLReader('testParserUDPWithData.xml')
        dest, src, proto = xml_reader.get_ethernet_frame_header()

        self.assertEqual(dest, '01:00:5E:7F:FF:FA')
        self.assertEqual(src, 'C0:4A:00:57:00:EE')
        self.assertEqual(proto, '8')

        version, header_length, ttl, protocol, source, target = xml_reader.get_ip_header()
        self.assertEqual(version, '4')
        self.assertEqual(header_length, '20')
        self.assertEqual(ttl, '4')
        self.assertEqual(protocol, '17')
        self.assertEqual(source, '192.168.0.1')
        self.assertEqual(target, '239.255.255.250')

        source_port, destination_port, length, data = xml_reader.get_udp_header()
        self.assertEqual(source_port, '32769')
        self.assertEqual(destination_port, '1900')
        self.assertEqual(length, '26174')
        #self.assertEqual(data, str(b'NOTIFY * HTTP/1.1\r\nHOST: 239.255.255.250:1900\r\nCACHE-CONTROL: max-age=100\r\nLOCATION: http://192.168.0.1:1900/igd.xml\r\nNT: uuid:9f0865b3-f5da-4ad5-85b7-7404637fdf37\r\nNTS: ssdp:alive\r\nSERVER: ipos/7.0 UPnP/1.0 TL-WR840N/1.0\r\nUSN: uuid:9f0865b3-f5da-4ad5-85b7-7404637fdf37\r\n\r\n', 'utf-8'))
        os.remove('testParserUDPWithData.xml')

if __name__ == '__main__':
    unittest.main()