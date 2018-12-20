
import pygame
import subprocess
import json
import Tkinter
from threading import Thread
from time import sleep
from tkFileDialog import askopenfilename

class CharMap:

    charMap = None
    collidableTiles = None
    JSONFileName = None
    mapFileName = None
    mapLength = 256
    rows = 16
    columns = 16
    pixelSize = 32

    def __init__(self, length, rows, columns, pixels):

        self.charMap = []
        self.collidableTiles = []
        self.mapLength = length
        self.rows = rows
        self.columns = columns
        self.pixelSize = pixels

    def setMap(self, charMap):

        self.charMap = charMap

    def clearMap(self):

        self.charMap = []

    def clearCollidableTiles(self):

        self.collidableTiles = []    

    def addCollidableTile(self, tile):

        self.collidableTiles.append(tile)       

global CharMapObject 
CharMapObject = CharMap(256, 16, 16, 32)

pygame.init()
window = pygame.display.set_mode((1024, 512))

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREY = (128, 128, 128) 

global locked
locked = False


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
savedJSON = "Saved map object to JSON"
savedMap = "Saved changes made to map file"
overSetCollisionButton = "Set selected tiles as collidable"
overRemoveCollisionButton = "Remove collidability from selected tiles"
setCollision = "Tiles made collidable"
removeCollision = "Collidability removed from tiles"
overSetConnectionsButton = "Create connection between selected tiles and another map"
overRemoveConnectionsButton = "Remove connection bettween selected tiles and other map"
setConnection = "Connection made from selected tiles to other map"
removeConnection = "Connection removed from selected tiles to other map"


borderImage = images["border"]
collisionImage = images["collision"]
mapConnection = images["mapConnection"]
loadButton = images["loadMap"]
tileButton = images["loadTile"]
JSONButton = images["saveJSON"]
saveMapButton = images["saveMap"]
collisionsOnButton = images["on"]
collisionsOffButton = images["off"]
connectionsOnButton = images["on"]
connectionsOffButton = images["off"]

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

collisionsOnButtonWidth = saveMapButton.get_width()
collisionsOnButtonHeight = saveMapButton.get_height()

xCollisionsOnButton = 570
yCollisionsOnButton = 375
window.blit(collisionsOnButton, (xCollisionsOnButton, yCollisionsOnButton))

collisionsOffButtonWidth = saveMapButton.get_width()
collisionsOffButtonHeight = saveMapButton.get_height()

xCollisionsOffButton = 650
yCollisionsOffButton = 375
window.blit(collisionsOffButton, (xCollisionsOffButton, yCollisionsOffButton))

connectionsOnButtonWidth = saveMapButton.get_width()
connectionsOnButtonHeight = saveMapButton.get_height()

xConnectionsOnButton = 570
yConnectionsOnButton = 425
window.blit(connectionsOnButton, (xConnectionsOnButton, yConnectionsOnButton))

connectionsOffButtonWidth = saveMapButton.get_width()
connectionsOffButtonHeight = saveMapButton.get_height()

xConnectionsOffButton = 650
yConnectionsOffButton = 425
window.blit(connectionsOffButton, (xConnectionsOffButton, yConnectionsOffButton))




def setCollidables(initialPosition):    

    for tile in tileList:
        CharMapObject.addCollidableTile(tile)

    print(CharMapObject.collidableTiles)    

def removeCollidables():

    global tileList

    for item in tileList:
        if item in CharMapObject.collidableTiles:
            CharMapObject.collidableTiles.remove(item)



def setMapConnections():
    print("???")

def removeMapConnections():
    print("!!!")



def drawCollidables():

    for index in CharMapObject.collidableTiles:
        xPosition = (index % CharMapObject.rows) * 32
        yPosition = (index / CharMapObject.rows) * 32 
        window.blit(collisionImage, (xPosition, yPosition))



def threadedPrintAction(action):
    
    printAction(action)

    thread = Thread(target=wait)	
    thread.start()


def wait():

    global locked
    locked = True
    sleep(5)
    locked = False

def clearMessage():
    
    pygame.draw.rect(window, WHITE, [550, 490, 480, 30])

def printAction(action):

    clearMessage()

    textFont = pygame.font.Font('freesansbold.ttf', 16)
    textSurface = textFont.render(action, True, BLACK)

    textRectangle = textSurface.get_rect() 
    textRectangle.left = 570 #(520, 500)
    textRectangle.top = 490 #(520, 500)

    window.blit(textSurface, textRectangle)

    # pygame.draw.rect(window, WHITE, [550, 490, 400, 30])





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

    drawCollidables()


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
            if len(tileList) == 0:    
                drawImage()

            position = (row + (column * 16))
            tileList.append(position)
            tileList = set(tileList)
            tileList = list(tileList)
            window.blit(borderImage, (xPosition, yPosition))
            keys = pygame.key.get_pressed()
            
            if not keys[pygame.K_RCTRL] and not keys[pygame.K_LCTRL]:
                tileList = []


            # position = (row + (column * 16))
            # selectedTile = position
            # window.blit(borderImage, (xPosition, yPosition))

            # keys = pygame.key.get_pressed()
            # if keys[pygame.K_RCTRL] or keys[pygame.K_LCTRL]:
            #     tileList.append(position)
            #     tileList = set(tileList)
            #     tileList = list(tileList)
            #     window.blit(borderImage, (xPosition, yPosition))
            # else:
            #     tileList = []

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

        rewriteMap(selectedTile, filePath[0])

        writeMapContents()
        drawImage()

def rewriteMap(tilePosition, tileChar):

    global tileList

    CharMapObject.charMap[tilePosition] = tileChar

    for index in tileList:
        CharMapObject.charMap[index] = tileChar

getImages()
loadImages()

position = 0

while True:

    xMouse, yMouse = pygame.mouse.get_pos()
    overLoadButton = onButton(xMouse, yMouse, xLoadButton, yLoadButton, loadButtonWidth, loadButtonHeight)
    overJSONButton = onButton(xMouse, yMouse, xJSONButton, yJSONButton, JSONButtonWidth, JSONButtonHeight)
    overTileButton = onButton(xMouse, yMouse, xTileButton, yTileButton, tileButtonWidth, tileButtonHeight)
    overSaveButton = onButton(xMouse, yMouse, xSaveMapButton, ySaveMapButton, saveMapButtonWidth, saveMapButtonHeight)
    overCollisionOnButton = onButton(xMouse, yMouse, xCollisionsOnButton, yCollisionsOnButton, collisionsOnButtonWidth, collisionsOnButtonHeight)
    overCollisionOffButton = onButton(xMouse, yMouse, xCollisionsOffButton, yCollisionsOffButton, collisionsOffButtonWidth, collisionsOffButtonHeight)    
    overConnectionOnButton = onButton(xMouse, yMouse, xConnectionsOnButton, yConnectionsOnButton, connectionsOnButtonWidth, connectionsOnButtonHeight)
    overConnectionOffButton = onButton(xMouse, yMouse, xConnectionsOffButton, yConnectionsOffButton, connectionsOffButtonWidth, connectionsOffButtonHeight)    

    position = checkMouseOver() 
    
    if len(CharMapObject.charMap) == 256 and position > 0:
        selectedTile = position

    pygame.display.flip()


    if overLoadButton and not locked:
        printAction(overLoadMapButton)

    elif overJSONButton and not locked:
        printAction(saveJSONMapButton)

    elif overTileButton and not locked:
        printAction(overLoadTileButton)

    elif overSaveButton and not locked:
        printAction(overSaveMapButton)

    elif overCollisionOnButton and not locked:
        printAction(overSetCollisionButton)

    elif overCollisionOffButton and not locked:
        printAction(overRemoveCollisionButton)

    elif overConnectionOnButton and not locked:
        printAction(overSetConnectionsButton)

    elif overConnectionOffButton and not locked:
        printAction(overRemoveConnectionsButton)

    elif not locked:
        clearMessage()

    for event in pygame.event.get():
    
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            clicked = True
            
            if overLoadButton:
                openBrowse()

            if overJSONButton:
                makeJSON(CharMapObject.JOSONFileName)
                threadedPrintAction(savedJSON)

            if overTileButton:
                redrawTiles(selectedTile)

            if overSaveButton:
                writeMapFile(CharMapObject.mapFileName)
                threadedPrintAction(savedMap)

            if overCollisionOnButton:
                setCollidables(position)    
                threadedPrintAction(setCollision)

            if overCollisionOffButton:
                removeCollidables()
                threadedPrintAction(removeCollision)

            if overConnectionOnButton:
                setMapConnections()
                threadedPrintAction(setConnection)

            if overConnectionOffButton:
                removeMapConnections()
                threadedPrintAction(removeConnection)


            if position == -2:
                tileList = []
                drawImage()



        else:
            clicked = False

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()




