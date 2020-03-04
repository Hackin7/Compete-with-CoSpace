
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
    
def mapData(size, pixels):
    data = [[0 for y in range(size[1])] for x in range(size[0])]
    #For a path
    for x in range(size[0]):
        for y in range(size[1]):
            '''
            (1,76,241) #Blue
            (227, 20, 27) #Orange
            (166,166,166) #Gray Slow Areas
            '''
            #if pix_val[i] == (1,76,241):#Blue
            #    data[x][y] = 0
            #if pix_val[x+y*size[1]] == (0,0,0): #Cannot travel
            #    data[x][y] = 1

            #if y < 100:data[x][y] = 1
            
            if pixels[x,y] == (0,168,243): #Light Blue 
                data[x][y] = 3
            if pixels[x,y] == (0,0,0): 
                data[x][y] = 1
                margin = 15
                #generate Margin around area to prevent collision with walls and stuff
                for m in range(1,margin):
                    for n in range(1, margin):
                        if x+m < size[0]:
                            if y+n < size[1]:
                                if pixels[x+m,y+n] != (0,0,0):  data[x+m][y+n] = 2
                            if y-n > 0:
                                if pixels[x+m,y-n] != (0,0,0):  data[x+m][y-n] = 2
                        if x+m > 0:
                            if y+n < size[1]:
                                if pixels[x-m,y+n] != (0,0,0):  data[x-m][y+n] = 2
                            if y-n > 0:
                                if pixels[x-m,y-n] != (0,0,0):  data[x-m][y-n] = 2
    return data

def switchYValues(data):
    newData = []
    for x in range(len(data)):
        yval = [0 for i in range(len(data[0]))]
        for y in range(len(data[0])):
            yval[y] = data[x][-y-1]
        newData.append(yval)
    return newData
    
def main(args):
    im = Image.open(input('Enter image file: '))
    im = resizeImage(im, 320)
    im.show()
    #pix_val = list(im.getdata())
    pixels = im.load()
    print(im.size)
    #print(mapData(im.size, pix_val))
    #print(pix_val)
    with open("./bitmappingTest.txt","w+") as file:
        file.write(str(switchYValues(mapData(im.size, pixels))))#pix_val)))
        #str(pix_val))
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
