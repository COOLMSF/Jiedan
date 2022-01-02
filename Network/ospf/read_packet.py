from scapy.all import *

def test(filepath):
    pcaps = rdpcap(filepath)
    for p in pcaps:
        print(p.show())

test("hello.pcapng")
