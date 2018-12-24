import pygame

pygame.init()
window = pygame.display.set_mode((512, 640))

cells = []

liveCell = pygame.image.load("alive.png").convert_alpha()

for index in range(0, 4096):
    cells.append(False)
    
    window.blit(liveCell, ((index % 64) * 8, (index / 64) * 8))

pygame.draw.rect(window, (128, 128, 128), [0, 512, 512, 128])

pygame.display.flip()

while True:

    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()