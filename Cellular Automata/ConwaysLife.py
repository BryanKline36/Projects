import pygame

pygame.init()
window = pygame.display.set_mode((512, 576))

cells = []

liveCell = pygame.image.load("alive.png").convert_alpha()
deadCell = pygame.image.load("dead.png").convert_alpha()
button = pygame.image.load("button.png").convert_alpha()

for index in range(0, 4096):
    cells.append(False)
    
    window.blit(liveCell, ((index % 64) * 8, (index / 64) * 8))

pygame.draw.rect(window, (128, 128, 128), [0, 512, 512, 128])

window.blit(button, (32, 544))
window.blit(button, (160, 544))
window.blit(button, (288, 544))
window.blit(button, (416, 544))


pygame.display.flip()

while True:

    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()