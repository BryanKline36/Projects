import pygame

pygame.init()
window = pygame.display.set_mode((512, 640))

cells = []

for index in range(0, 64):
    cells[index] = False



while True:

    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()