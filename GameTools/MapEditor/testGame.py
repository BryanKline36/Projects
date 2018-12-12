
import pygame
import subprocess
import json
import Tkinter
from tkFileDialog import askopenfilename

class CharMap:

    charMap = None
    JSONFileName = None
    mapFileName = None
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

        self.charMap = charMap

    def clearMap(self):

        self.charMap = []

global CharMapObject 
CharMapObject = CharMap(256, 16, 16, 32)

pygame.init()
window = pygame.display.set_mode((1024, 512))

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREY = (128, 128, 128) 

global imageDictionary
imageDictionary = {}

global images
images = {}

global tileList
tileList = []

clicked = False
fileLoaded = False

def getImages():

    directoryPath = "ls images/"

    directoryContents = subprocess.Popen(directoryPath, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    for item in directoryContents.stdout.readlines():
        key = item.split('.')[0]
        imageDictionary[key] = "images/" + item[:-1]

def loadImages():
    
    for key in imageDictionary:
        images[key] = pygame.image.load(imageDictionary[key]).convert_alpha()

getImages()
loadImages()

overLoadMapButton = "Load a map file"
overLoadTileButton = "Load map tile"
saveJSONMapButton = "Save map to JSON"
overSaveMapButton = "Save changes to map file"


borderImage = images["border"]
loadButton = images["loadMap"]
tileButton = images["loadTile"]
JSONButton = images["saveJSON"]
saveMapButton = images["saveMap"]

window.fill(WHITE)
pygame.draw.rect(window, GREY, [0,0,512,512])
pygame.draw.rect(window, GREY, [570, 10, 256, 256])

loadButtonWidth = loadButton.get_width()
loadButtonHeight = loadButton.get_height()

xLoadButton = 570
yLoadButton = 280
window.blit(loadButton, (xLoadButton, yLoadButton))

tileButtonWidth = loadButton.get_width()
tileButtonHeight = loadButton.get_height()

xTileButton = 570
yTileButton = 328
window.blit(tileButton, (xTileButton, yTileButton))

JSONButtonWidth = JSONButton.get_width()
JSONButtonHeight = JSONButton.get_height()

xJSONButton = 650
yJSONButton = 280
window.blit(JSONButton, (xJSONButton, yJSONButton))

saveMapButtonWidth = saveMapButton.get_width()
saveMapButtonHeight = saveMapButton.get_height()

xSaveMapButton = 650
ySaveMapButton = 328
window.blit(saveMapButton, (xSaveMapButton, ySaveMapButton))

def makeJSON(fileName):

    JSONObject = json.dumps(CharMapObject.__dict__)

    jsonFile = open(fileName, "w")
    jsonFile.write(JSONObject)

def openBrowse():

    browseFile = Tkinter.Tk()
    browseFile.withdraw()
    filePath = askopenfilename(filetypes=[("", "*.map")],)
    CharMapObject.mapFileName = filePath
    
    if type(CharMapObject.mapFileName) == str:
        setJSONFileName(CharMapObject.mapFileName)
        CharMapObject.clearMap()
        readMapFile(CharMapObject.mapFileName)
        writeMapContents()
        drawImage()
        
        fileLoaded = True

def setJSONFileName(filePath):

        fileName = filePath.split('/')
        fileName = fileName[len(fileName) - 1]
        fileName = fileName.split('.')
        CharMapObject.JOSONFileName = fileName[0] + ".JSON"

def drawImage():

    counter = 0
    xPosition = 0 
    yPosition = 0
    image = None

    for character in CharMapObject.charMap:

        if counter != 0 and counter % CharMapObject.columns == 0:
            xPosition = 0
            yPosition += CharMapObject.pixelSize

        window.blit(images[character], (xPosition, yPosition))

        pygame.display.flip()

        counter += 1
        xPosition += CharMapObject.pixelSize


def writeMapFile(fileName):

    if fileName != None and fileName != '':
        file = open(fileName, "w")

        counter = 0
        for character in CharMapObject.charMap:
            file.write(character)

            if counter != 0 and counter % 16 == 0:  
                file.write('\n')



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

def onButton(xMouse, yMouse, xButton, yButton, buttonWidth, buttonHeight):

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


selectedTile = -1

def checkMouseOver():

    global tileList

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
            selectedTile = position
            drawImage()
            window.blit(borderImage, (xPosition, yPosition))

            keys = pygame.key.get_pressed()
            if keys[pygame.K_RCTRL] or keys[pygame.K_LCTRL]:
                tileList.append(position)
                print(tileList)
            else:
                tileList = []
    else:
        position = -2        

    return position

def redrawTiles(selectedTile):

    browseFile = Tkinter.Tk()
    browseFile.withdraw()
    filePath = askopenfilename(initialdir="images")


    if type(filePath) == str:
        filePath = filePath.split("/")
        filePath = filePath[len(filePath) - 1]
        CharMapObject.charMap[selectedTile] = filePath[0]

        writeMapContents()
        drawImage()
        

getImages()
loadImages()

position = 0

while True:

    xMouse, yMouse = pygame.mouse.get_pos()
    overLoadButton = onButton(xMouse, yMouse, xLoadButton, yLoadButton, loadButtonWidth, loadButtonHeight)
    overJSONButton = onButton(xMouse, yMouse, xJSONButton, yJSONButton, JSONButtonWidth, JSONButtonHeight)
    overTileButton = onButton(xMouse, yMouse, xTileButton, yTileButton, tileButtonWidth, tileButtonHeight)
    overSaveButton = onButton(xMouse, yMouse, xSaveMapButton, ySaveMapButton, saveMapButtonWidth, saveMapButtonHeight)
    position = checkMouseOver() 
    
    if len(CharMapObject.charMap) == 256 and position > 0:
        selectedTile = position

    pygame.display.flip()

    for event in pygame.event.get():
    
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            clicked = True
            

            if overLoadButton:
                openBrowse()

            if overJSONButton:
                makeJSON(CharMapObject.JOSONFileName)

            if overTileButton:
                redrawTiles(selectedTile)

            if overSaveButton:
               writeMapFile(CharMapObject.mapFileName)

            if position == -2:
                tileList = []
                drawImage()


        else:
            clicked = False

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()




