import struct
import textwrap
import socket

class PacketParser(object):

    def __init__(self, **kwargs):
        self.next_parsers = {}

        for key, value in kwargs.items():
            self.next_parsers[key] = value

        print(self.next_parsers)

    def parse_header(self, data):
        print('handle request in a base class')
