import pygame



pygame.init()
window = pygame.display.set_mode((1024, 512))

waterimage = pygame.image.load("w.png")
grassimage = pygame.image.load("g.png")

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




def message_display(text):
    largeText = pygame.font.Font('freesansbold.ttf', 16)
    TextSurf, TextRect = text_objects(text, largeText)
    TextRect.center = (576, 64)
    window.blit(TextSurf, TextRect)

def text_objects(text, font):
    textSurface = font.render(text, True, (255,255,255))
    return textSurface, textSurface.get_rect()    

while True:

    drawImage()
    message_display("thing")


    pygame.display.flip()


    # window.fill(black)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            
            print(map)
            pygame.quit()
