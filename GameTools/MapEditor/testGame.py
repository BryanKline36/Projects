import pygame
import Tkinter
from tkFileDialog import askopenfilename

pygame.init()
window = pygame.display.set_mode((1024, 512))

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

waterimage = pygame.image.load("w.png")
grassimage = pygame.image.load("g.png")
newGameButton = pygame.image.load("base.png").convert_alpha()
window.fill(WHITE)

map = []

buttonWidth = newGameButton.get_width()
buttonHeight = newGameButton.get_height()

xButton = 800
yButton = 300
window.blit(newGameButton, (xButton, yButton))

fileRead = False

def openBrowse():

    browseFile = Tkinter.Tk()
    browseFile.withdraw()
    filePath = askopenfilename(filetypes=[("", "*.map")],)
    
    if type(filePath) == str:
        del map[:]
        readMapFile(filePath)
        writeMapContents()

def drawImage():

    counter = 0
    xPosition = 0 
    yPosition = 0
    image = None

    for character in map:

        if counter != 0 and counter % 16 == 0:
            xPosition = 0
            yPosition += 32

        if character == "w":
            window.blit(waterimage, (xPosition, yPosition))

        if character == "g":
            window.blit(grassimage, (xPosition, yPosition))

        pygame.display.flip()

        counter += 1
        xPosition += 32


def readMapFile(fileName):

    file = open(fileName, "r")

    for line in file:

        for char in line:

            if char != '\n':    
                map.append(char)


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

    for character in map:

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
        openBrowse()
        return True
    else:
        return False


while True:

    if fileRead:
        drawImage()

    xMouse, yMouse = pygame.mouse.get_pos()
    fileRead = onButton(xMouse, yMouse)
    
    pygame.display.flip()

    for event in pygame.event.get():
    
        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()




