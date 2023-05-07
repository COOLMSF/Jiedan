import sys
import os
import numpy,scipy, os, array, scipy.misc
from PIL import Image

width = 256

class Exec2img():
    def __init__(self) -> None:
        pass
    
    def exec2img(self, src :str, dst :str):
        filename = src

        f = open(filename,'rb')
        ln = os.path.getsize(filename); # length of file in bytes
        rem = ln%width 

        a = array.array("B") # uint8 array
        a.fromfile(f,ln-rem)
        f.close(); 
        
        g = numpy.reshape(a,(int(len(a)/width),width))
        g = numpy.uint8(g)

        im = Image.frombuffer('L', (width,int(len(a)/width)), g, 'raw', 'L', 0, 1)
        print(filename)
        im.save(dst)
