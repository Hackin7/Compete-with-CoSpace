# convert output diarrhea into something usablefrom PIL import Image

import sys
sys.path.append('./Python_Libraries/')
from PreprocessedMap import data
from ImageCalculation import *

map1 = [int(i) for i in input("Data:").split(',_')]
#6,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_0,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_6,_5,_6,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5,_5
def getMap(i,j):
    try:return map1[i*width+j]
    except: return 1
width = 360
height = 270
data = [ [getMap(i,j) for j in range(height)] for i in range(width)]

img, pixels = convertBack(data)
img.show()
