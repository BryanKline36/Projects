import pygame



pygame.init()
window = pygame.display.set_mode((1024, 512))

waterimage = pygame.image.load("w.png")
grassimage = pygame.image.load("g.png")
window.fill((255, 255, 255))

map = []

                 



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

def readMapFile():

    file = open("testMap.map", "r")

    for line in file:

        for char in line:

            if char != '\n':    

                map.append(char)


readMapFile()




def writeText(text, xPosition, yPosition):

    textFont = pygame.font.Font('freesansbold.ttf', 16)
    textSurface = textFont.render(text, True, (0,0,0))

    textRectangle = textSurface.get_rect() 
    textRectangle.center = (xPosition, yPosition)

    window.blit(textSurface, textRectangle)

def writeMapContents():

    charCounter = 0
    xPosition = 576
    yPosition = 8
    for i in map:

        if charCounter == 16:
            
            charCounter = 0
            xPosition = 576
            yPosition += 16

        writeText(i, xPosition, yPosition)

        charCounter += 1
        xPosition += 16

writeMapContents()

while True:

    drawImage()
    # writeText("thing", 576, 64)


    pygame.display.flip()



    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            
            print(map)
            writeMapContents()
            pygame.quit()
