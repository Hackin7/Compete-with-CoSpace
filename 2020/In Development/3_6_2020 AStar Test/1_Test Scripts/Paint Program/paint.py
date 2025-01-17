from tkinter import *
from tkinter.filedialog import askopenfilename
from PIL import Image
from PIL import ImageTk
from PIL import ImageGrab
from ctypes import windll #Makes app DPI Aware
user32 = windll.user32
user32.SetProcessDPIAware()

###Drawing Path
stack = [0,0,0,0]
text_ids=[]

import sys,os
from sys import stdin, stdout
sys.path.append('../Python_Libraries/')
from ImageCalculation import *
def cppInput(x1, y1, x2, y2):
    #os.system("g++ AStar/astar.cpp -o astar.exe") #Compile on the spot
    cmd = os.popen(f'cd AStar && echo {x1} {y1} {x2} {y2} | astar.exe').read()
    #cmd = os.popen(f'echo {x1} {y1} {x2} {y2} | ./astar').read()
    with open("path.txt","w") as f:
        f.write(cmd)
    lines = cmd.split("\n")
    print(lines[-1])
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

def imageObj(im):
    print(stack)
    lines = cppInput(stack[0],stack[1],stack[2],stack[3])
    coordinates = inputToCoordinates(lines)
    newMap = switchYValues(mapData(im.size, pixels))
    newImg, newPixels = convertBack(newMap)
    addCoordinates(coordinates, newPixels,(100,100,0))
    return newImg#newImg.show()

if __name__ == "__main__":
    root = Tk()

    # open image and set width and height
    File = askopenfilename(parent=root, initialdir="C:/",title='Choose an image.')
    im = Image.open(File)
    widths, heights = im.size
    img = ImageTk.PhotoImage(im)

    #im, pixels = convertBack(data)
    #widths, heights = im.size
    #img=ImageTk.PhotoImage(im)
    
    #setting up a tkinter canvas with scrollbars
    frame = Frame(root, bd=2, relief=SUNKEN,height=heights,width=widths)
    frame.grid_rowconfigure(0, weight=1)
    frame.grid_columnconfigure(0, weight=1)
    canvas = Canvas(frame, bd=0)
    canvas.grid(row=0, column=0, sticky=N+S+E+W)
    frame.pack(fill=BOTH,expand=1)

    #adding the image
    canvasImage = canvas.create_image(0,0,image=img,anchor="nw")
    # canvas.config(scrollregion=canvas.bbox(ALL))

    #function to be called when mouse is clicked
    def printcoords(event):
        global text_ids
        text_id = canvas.create_text(event.x,event.y,text='X',font = "Times 20 italic bold")
        if len(text_ids)>=2:
            canvas.delete(text_ids[0])
            text_ids = text_ids[1:]
        text_ids.append(text_id)
        
        x = round(event.x/(widths/360))
        y = round((heights-event.y)/(heights/270))
        stack.pop(0)
        stack.pop(0)
        stack.append(x)
        stack.append(y)
        newim = imageObj(im)
        '''
        if stack[0]!=0 or stack[1] !=0 :
            #newim.show()
            newimg = ImageTk.PhotoImage(newim)
            canvas.itemconfig(canvasImage, image=newimg,anchor="nw")
            #Some random code to enable it to actually display the image
            canvasImage.image = img
        '''
        #outputting x and y coords to console
        print(x,y)   	

    
        
    #mouseclick event
    canvas.bind("<Button 1>",printcoords)

    #Create buttons
    #Quit when done
    #Create buttons
    def resetImg():
        canvas.itemconfig(canvasImage, image=img,anchor="nw")
    remove_button = Button(root,text='Reset',command= resetImg)
    remove_button.pack(side='bottom')
    

    root.mainloop()
	
	
	
	
	
	
	
