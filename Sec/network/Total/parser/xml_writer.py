from xml.dom import minidom


class XMLWriter:

    __instance = None

    def __init__(self):
        self._path = ''
        self.doc = minidom.Document()
        self.root = self.doc.createElement('data')
        self.doc.appendChild(self.root)

        if XMLWriter.__instance != None:
            raise Exception("This class is a singleton!")
        else:
            XMLWriter.__instance = self

    def setPath(self, path):
        self._path = path

    @staticmethod
    def getXMLWriter():
        """ Static access method. """
        if XMLWriter.__instance == None:
            XMLWriter()
        return XMLWriter.__instance

    def save_ethernet_frame_header(self, *args):
        eth_elem = self.doc.createElement('ethernet_frame')
        self.root.appendChild(eth_elem)

        fields = ['Destination', 'Source', 'Protocol']
        i = 0
        for field in args:
            print('i = ', i)
            item = self.doc.createElement(fields[i])
            text = self.doc.createTextNode('{}'.format(field))
            item.appendChild(text)
            eth_elem.appendChild(item)
            i += 1

    def save_ip_header(self, *args):
        ipv4_elem = self.doc.createElement('ipv4_header')
        self.root.appendChild(ipv4_elem)

        fields = ['Version', 'Header_length', 'TTL', 'Protocol', 'Source', 'Target']
        i = 0
        for field in args:
            item = self.doc.createElement(fields[i])
            text = self.doc.createTextNode('{}'.format(field))
            item.appendChild(text)
            ipv4_elem.appendChild(item)
            i += 1

    def save_tcp_header(self, *args):
        tcp_elem = self.doc.createElement('tcp_header')
        self.root.appendChild(tcp_elem)

        fields = ['SourcePort', 'DestinationPort', 'Sequence', 'Acknowledgement', 'Data']
        i = 0
        for field in args:
            item = self.doc.createElement(fields[i])
            text = self.doc.createTextNode('{}'.format(field))
            item.appendChild(text)
            tcp_elem.appendChild(item)
            i += 1

    def save_udp_header(self, *args):
        udp_elem = self.doc.createElement('udp_header')
        self.root.appendChild(udp_elem)

        fields = ['SourcePort', 'DestinationPort', 'Length', 'Data']
        i = 0
        for field in args:
            item = self.doc.createElement(fields[i])
            text = self.doc.createTextNode('{}'.format(field))
            item.appendChild(text)
            udp_elem.appendChild(item)
            i += 1

    def save_to_xml_file(self):
        xml_str = self.doc.toprettyxml(indent="  ")
        with open(self._path, "a") as f:
            f.write(xml_str)

        self.doc = minidom.Document()
        self.root = self.doc.createElement('data')
        self.doc.appendChild(self.root)
