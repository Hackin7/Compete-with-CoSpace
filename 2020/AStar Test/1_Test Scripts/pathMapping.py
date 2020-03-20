from PIL import Image

import sys
sys.path.append('./Python_Libraries/')
from ImageCalculation import *

def standardInputLines():
    lines = []
    while True:
        data = input()
        if data == "": break
        lines.append(data)
    return lines

def cppInput(x1, y1, x2, y2):
    #os.system("g++ AStar/astar.cpp -o astar.exe") #Compile on the spot
    cmd = os.popen(f'cd AStar && echo {x1} {y1} {x2} {y2} | astar.exe').read()
    #cmd = os.popen(f'echo {x1} {y1} {x2} {y2} | ./astar').read()
    lines = cmd.split("\n")
    return lines[:-1]
    
def inputToCoordinates(lines):
    coordinates = []
    for line in lines:
        coordinates.append( [int(i) for i in line.split()] )
    return coordinates
    
def addCoordinates(coordinates, pixels, colour):
    try:
        for x,y in coordinates:
            pixels[x,-y-1] = colour
    except:pass

def run(mapname="map.txt",size=361,pathname="path.txt"):
    print(mapname,pathname)
    layout=[]
    with open("C:/Users/zunmu/Microsoft Robotics Dev Studio 4/"+mapname) as m:
        for j in range(360):
            data = m.readline()
            #print(data)
            if data=="":break
            data = [int(i) for i in data.split()]
            layout = [data]+layout

    with open("C:/Users/zunmu/Microsoft Robotics Dev Studio 4/"+"zone.txt") as m:
        for j in range(360):
            data = m.readline()
            #print(data)
            if data=="":break
            zoning = data.split()
            for i in range(len(zoning)):
                if int(zoning[i]) > 0:
                    layout[-j][i] = 5

    print(f"Getting Map {len(layout)}")
    lines = []        
    with open("C:/Users/zunmu/Microsoft Robotics Dev Studio 4/"+pathname) as p:
        while True:
            data = p.readline()
            if data == "":break
            lines.append(data)
    coordinates = inputToCoordinates(lines)
    newMap = switchYValues(mapData(im.size, pixels))
    newImg, newPixels = convertBack(layout)
    addCoordinates(coordinates, newPixels,(100,100,0))
    newImg.show()

def r():
    while True:
        try:run()
        except KeyboardInterrupt:pass 
        except Exception as e:
            print(e)
        input("Get Map again")
import os
from PreprocessedMap import data
if __name__ == '__main__':
    print("Show the Path on the Image")
    print("Make sure to compile astar.cpp into astar.exe first")
    #imageFile = "ZonedGuessed.png"#input('Enter image file: ')
    #im = Image.open(imageFile)
    #im = resizeImage(im, 360)
    #im.show()
    #pixels = im.load()
    im, pixels = convertBack(data)
    print(im.size)

   
    #lines = standardInputLines()

    x1, y1, x2, y2 = 125, 95, 256, 211
    try:
        x1, y1, x2, y2 = [int(i) for i in input("Enter coordinates in the form x1,y1,x2,y2:").split(",")]
        lines = cppInput(x1, y1, x2, y2)
        print("Path Length:",len(lines))
        coordinates = inputToCoordinates(lines)

        newMap = switchYValues(mapData(im.size, pixels))
        newImg, newPixels = convertBack(newMap)
        addCoordinates(coordinates, newPixels,(100,100,0))
        newImg.show()
    except Exception as e:
        print(e)
        print("RUN")
        r()
    #x1, y1 = 30, 30
   

    


