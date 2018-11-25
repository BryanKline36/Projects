import pygame

pygame.init()
window = pygame.display.set_mode((512, 512))

waterimage = pygame.image.load("w.png")
grassimage = pygame.image.load("g.png")

map = []

def drawImage():

    xPosition = 0 
    yPosition = 0

    for i in range(256):

        if i != 0 and i % 16 == 0:

            xPosition = 0
            yPosition += 32

        window.blit(waterimage, (xPosition, yPosition))
        pygame.display.flip()

        xPosition += 32

def readMapFile():

    file = open("testMap.map", "r")

    for item in file:
        map.append(item[:-1])


readMapFile()

while True:





    drawImage()


    # window.fill(black)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            
            print(map)
            pygame.quit()
