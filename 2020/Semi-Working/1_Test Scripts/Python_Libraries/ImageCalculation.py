from PIL import Image

def resizeImage(img, x=0, y=0):
    if x == 0 and y == 0:
        return None
    elif x == 0:
        hpercent = (y/float(img.size[1]))
        x = int((float(img.size[0])*float(hpercent)))
    elif y == 0:
        wpercent = (x/float(img.size[0]))
        y = int((float(img.size[1])*float(wpercent)))
    return img.resize((x,y), Image.ANTIALIAS)    

#Unexplored
#Deposit
#Red
#Blue
#Black
#Wall
# Border
colourData = [(-1,(0,100,0)),\
              (1, (0,255,0)),\
              (2, (255,0,0)),\
              (3, (0,0,255)),\
              (4, (0,168,243)),\
              (5, (0,0,0)),\
              (6, (100,0,0)),\
              (9,(0,0,100))]
def addBorder(size,pixels,data,x,y, colorval, borderval, margin):
    #generate Margin around area to prevent collision with walls and stuff
    for m in range(1,margin):
        for n in range(1, margin):
            if x+m < size[0]:
                if y+n < size[1]:
                    if pixels[x+m,y+n] != colorval:  data[x+m][y+n] = borderval
                if y-n > 0:
                    if pixels[x+m,y-n] != colorval:  data[x+m][y-n] = borderval
            if x+m > 0:
                if y+n < size[1]:
                    if pixels[x-m,y+n] != colorval:  data[x-m][y+n] = borderval
                if y-n > 0:
                    if pixels[x-m,y-n] != colorval:  data[x-m][y-n] = borderval

border = 6
borderColour = (0,0,100)
wall = 5
wallColour = (0,0,0)

def addPerimeter(data, borderval, border):
    for x in range(len(data)):
        for y in range(border):
            if data[x][y] != wall:
                data[x][y] = borderval
            if data[x][-y-1] != wall:
                data[x][-y-1] = borderval
    for y in range(len(data[0])):
        for x in range(border):
            if data[x][y] != wall:
                data[x][y] = borderval
            if data[-x-1][y] != wall:
                data[-x-1][y] = borderval


def mapData(size, pixels, leeway=10,perimeter=10):
    data = [[0 for y in range(size[1])] for x in range(size[0])] #Walkable
    #For a path
    for x in range(size[0]):
        for y in range(size[1]):
            '''
            (1,76,241) #Blue
            (227, 20, 27) #Orange
            (166,166,166) #Gray Slow Areas
            if pixels[x,y] == (0,100,0):
                data[x][y] = -1 #Unexplored
            if pixels[x,y] == (0,168,243): #Light Blue #Black Zone 
                data[x][y] = 4
            if pixels[x,y] == (0,0,255): #Blue Zone
                data[x][y] = 3
            if pixels[x,y] == (255,0,0): #Red Zone
                data[x][y] = 2
            if pixels[x,y] == (0,255,0): #Deposit Zone
                data[x][y] = 1
            '''
            currentcolour = pixels[x,y]
            if len(currentcolour)==4:
                currentcolour=(currentcolour[0],currentcolour[1],currentcolour[2])
            for val, colour in colourData:
                if currentcolour == colour and (data[x][y] != border and data[x][y] != wall):
                    data[x][y] = val
            
            if currentcolour == borderColour: #slow
                data[x][y] = 9
                addBorder(size,pixels,data,x,y,borderColour,border,leeway)
            if currentcolour == wallColour: #Border
                data[x][y] = 5
                addBorder(size,pixels,data,x,y,wallColour,border,leeway)
        addPerimeter(data, border, perimeter)
    return data

def switchYValues(data):
    newData = []
    for x in range(len(data)):
        yval = [0 for i in range(len(data[0]))]
        for y in range(len(data[0])):
            yval[y] = data[x][-y-1]
        newData.append(yval)
    return newData

def convertBack(data):
    img = Image.new('RGB', (len(data), len(data[0])), (255,255,255))
    pixels = img.load()
    for i in range(len(data)):
        for j in range(len(data[i])):
            for val, colour in colourData:
                if data[i][-j-1] == val:
                    pixels[i,j] = colour
    return img, pixels
