
import pygame
import json
import Tkinter
from tkFileDialog import askopenfilename

class CharMap:

    charMap = None
    mapLength = 256
    rows = 16
    columns = 16
    pixelSize = 32

    def __init__(self, length, rows, columns, pixels):

        self.charMap = []
        self.mapLength = length
        self.rows = rows
        self.columns = columns
        self.pixelSize = pixels

    def setMap(self, charMap):

        self.__charMap = charMap

    def clearMap(self):

        self.__charMap = []

global CharMapObject 
CharMapObject = CharMap(256, 16, 16, 32)
print(CharMapObject.pixelSize)

pygame.init()
window = pygame.display.set_mode((1024, 512))

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

waterimage = pygame.image.load("w.png")
grassimage = pygame.image.load("g.png")
zimage = pygame.image.load("border.png")

newGameButton = pygame.image.load("base.png").convert_alpha()
window.fill(WHITE)

map = []

buttonWidth = newGameButton.get_width()
buttonHeight = newGameButton.get_height()

xButton = 800
yButton = 300
window.blit(newGameButton, (xButton, yButton))

clicked = False
fileLoaded = False

def makeJSON(fileName):

    JSONObject = json.dumps(CharMapObject.__dict__)

    jsonFile = open(fileName, "w")
    jsonFile.write(JSONObject)


def openBrowse():

    browseFile = Tkinter.Tk()
    browseFile.withdraw()
    filePath = askopenfilename(filetypes=[("", "*.map")],)
    
    if type(filePath) == str:
        del map[:]
        CharMapObject.clearMap()
        readMapFile(filePath)
        writeMapContents()
        drawImage()
        fileLoaded = True

def drawImage():

    counter = 0
    xPosition = 0 
    yPosition = 0
    image = None

    for character in CharMapObject.charMap:

        if counter != 0 and counter % CharMapObject.columns == 0:
            xPosition = 0
            yPosition += CharMapObject.pixelSize

        if character == "w":
            window.blit(waterimage, (xPosition, yPosition))

        if character == "g":
            window.blit(grassimage, (xPosition, yPosition))

        pygame.display.flip()

        counter += 1
        xPosition += CharMapObject.pixelSize


def readMapFile(fileName):

    if fileName != None and fileName != '':
        file = open(fileName, "r")

        for line in file:

            for char in line:

                if char != '\n':    
                    CharMapObject.charMap.append(char)


def writeText(text, xPosition, yPosition):

    textFont = pygame.font.Font('freesansbold.ttf', 16)
    textSurface = textFont.render(text, True, BLACK)

    textRectangle = textSurface.get_rect() 
    textRectangle.center = (xPosition, yPosition)

    window.blit(textSurface, textRectangle)

def writeMapContents():

    charCounter = 0
    xPosition = 576
    yPosition = 16

    pygame.draw.rect(window, WHITE, [570, 10, 256, 256])

    for character in CharMapObject.charMap:

        if charCounter == 16:
            charCounter = 0
            xPosition = 576
            yPosition += 16

        writeText(character, xPosition, yPosition)

        charCounter += 1
        xPosition += 16

def onButton(xMouse, yMouse):

    if xMouse > xButton and xMouse < (xButton + buttonWidth):
        xInside = True
    else: 
        xInside = False
    
    if yMouse > yButton and yMouse < (yButton + buttonHeight):
        yInside = True
    else:
        yInside = False

    if xInside and yInside:
        return True
    else:
        return False

def checkMouseOver():

    row = 0
    column = 0
    xPosition = 0
    yPosition = 0
    position = -1

    xMouse, yMouse = pygame.mouse.get_pos()

    if xMouse > 0 and xMouse < 512 and yMouse > 0 and yMouse < 512:
        
        row = int(xMouse / 32)
        column = int(yMouse / 32)
        
        xPosition = row * 32
        yPosition = column * 32

        if clicked:
            position = (row + (column * 16))
            drawImage()
            window.blit(zimage, (xPosition, yPosition))

    return position

position = 0

while True:

    xMouse, yMouse = pygame.mouse.get_pos()
    overButton = onButton(xMouse, yMouse)
    position = checkMouseOver()
    
    if len(CharMapObject.charMap) == 256 and position != -1:
        print(CharMapObject.charMap[position])

    pygame.display.flip()

    for event in pygame.event.get():
    
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            clicked = True

            if overButton:
                openBrowse()
        else:
            clicked = False

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()




