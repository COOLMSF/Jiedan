from xml.dom import minidom


class XMLReader:

    def __init__(self, path):
        self._path = path

    def get_ethernet_frame_header(self):
        doc = minidom.parse(self._path)
        dest = doc.getElementsByTagName("Destination")[0].firstChild.data
        src = doc.getElementsByTagName("Source")[0].firstChild.data
        proto = doc.getElementsByTagName("Protocol")[0].firstChild.data

        return dest, src, proto

    def get_ip_header(self):
        doc = minidom.parse(self._path)

        version = doc.getElementsByTagName("Version")[0].firstChild.data

        header_length = doc.getElementsByTagName("Header_length")[0].firstChild.data

        ttl = doc.getElementsByTagName("TTL")[0].firstChild.data

        protocol = doc.getElementsByTagName("Protocol")[1].firstChild.data

        source = doc.getElementsByTagName("Source")[1].firstChild.data

        target = doc.getElementsByTagName("Target")[0].firstChild.data

        return version, header_length, ttl, protocol, source, target

    def get_tcp_header(self):
        doc = minidom.parse(self._path)

        source_port = doc.getElementsByTagName("SourcePort")[0].firstChild.data

        destination_port = doc.getElementsByTagName("DestinationPort")[0].firstChild.data

        sequence = doc.getElementsByTagName("Sequence")[0].firstChild.data

        acknowledgement = doc.getElementsByTagName("Acknowledgement")[0].firstChild.data

        data = doc.getElementsByTagName("Data")[0].firstChild.data

        return source_port, destination_port, sequence, acknowledgement, data

    def get_udp_header(self):
        doc = minidom.parse(self._path)

        source_port = doc.getElementsByTagName("SourcePort")[0].firstChild.data

        destination_port = doc.getElementsByTagName("DestinationPort")[0].firstChild.data

        length = doc.getElementsByTagName("Length")[0].firstChild.data

        data = doc.getElementsByTagName("Data")[0].firstChild.data

        return source_port, destination_port, length, data
