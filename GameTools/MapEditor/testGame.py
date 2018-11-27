import pygame
import Tkinter
from tkFileDialog import askopenfilename



pygame.init()
window = pygame.display.set_mode((1024, 512))

waterimage = pygame.image.load("w.png")
grassimage = pygame.image.load("g.png")
window.fill((255, 255, 255))

map = []
result = None



def openBrowse():

    tk_root = Tkinter.Tk()
    tk_root.withdraw()
    result = askopenfilename(filetypes=[("", "*.map")],)

    readMapFile(result)

    writeMapContents()

    return True

                 
button_x = 800
button_y = 300
newGameButton = pygame.image.load("base.png").convert_alpha()
x_len = newGameButton.get_width()
y_len = newGameButton.get_height()
# mos_x, mos_y = pygame.mouse.get_pos()
# if mos_x>button_x and (mos_x<button_x+x_len):
#     x_inside = True
# else: x_inside = False
# if mos_y>button_y and (mos_y<button_y+y_len):
#     y_inside = True
# else: y_inside = False
# if x_inside and y_inside:
    #Mouse is hovering over button
# screen.blit(newGameButton, (button_x,button_y))

print(result)

def drawImage():

    xPosition = 0 
    yPosition = 0
    image = None

    for i in range(256):

        if i != 0 and i % 16 == 0:

            xPosition = 0
            yPosition += 32

        if map[i] == "w":

            window.blit(waterimage, (xPosition, yPosition))

        if map[i] == "g":

            window.blit(grassimage, (xPosition, yPosition))

        pygame.display.flip()

        xPosition += 32

def readMapFile(fileName):

    file = open(fileName, "r")

    for line in file:

        for char in line:

            if char != '\n':    

                map.append(char)


# readMapFile()




def writeText(text, xPosition, yPosition):

    textFont = pygame.font.Font('freesansbold.ttf', 16)
    textSurface = textFont.render(text, True, (0,0,0))

    textRectangle = textSurface.get_rect() 
    textRectangle.center = (xPosition, yPosition)

    window.blit(textSurface, textRectangle)

def writeMapContents():

    charCounter = 0
    xPosition = 576
    yPosition = 16
    for i in map:

        if charCounter == 16:
            
            charCounter = 0
            xPosition = 576
            yPosition += 16

        writeText(i, xPosition, yPosition)

        charCounter += 1
        xPosition += 16

# writeMapContents()

window.blit(newGameButton, (button_x,button_y))

fileRead = False
while True:

    if fileRead:
        drawImage()


    x_len = newGameButton.get_width()
    y_len = newGameButton.get_height()
    mos_x, mos_y = pygame.mouse.get_pos()
    if mos_x>button_x and (mos_x<button_x+x_len):
        x_inside = True
    else: x_inside = False
    if mos_y>button_y and (mos_y<button_y+y_len):
        y_inside = True
    else: y_inside = False
    if x_inside and y_inside:
        fileRead = openBrowse()


    pygame.display.flip()

    for event in pygame.event.get():
    
        if event.type == pygame.QUIT:
            
            print(map)
            pygame.quit()




