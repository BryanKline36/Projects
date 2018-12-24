import pygame

pygame.init()
window = pygame.display.set_mode((512, 576))


def drawText(text, xPostion, yPosition):

    textFont = pygame.font.Font('freesansbold.ttf', 16)
    textSurface = textFont.render(text, True, (0, 0, 0))

    textRectangle = textSurface.get_rect() 
    textRectangle.left = xPostion
    textRectangle.top = yPosition

    window.blit(textSurface, textRectangle)

cells = []

liveCell = pygame.image.load("alive.png").convert_alpha()
deadCell = pygame.image.load("dead.png").convert_alpha()
button = pygame.image.load("button.png").convert_alpha()

for index in range(0, 4096):
    cells.append(False)
    
    window.blit(liveCell, ((index % 64) * 8, (index / 64) * 8))

pygame.draw.rect(window, (128, 128, 128), [0, 512, 512, 128])

window.blit(button, (32, 528))
window.blit(button, (160, 528))
window.blit(button, (288, 528))
window.blit(button, (416, 528))

drawText("Start", 45, 535)
drawText("Stop", 175, 535)
drawText("Faster", 297, 535)
drawText("Slower", 422, 535)






pygame.display.flip()

while True:

    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()