
import pygame
import Constants
import Automaton
from math import sqrt
from time import sleep

# Free functions

def drawText(text, xPostion, yPosition):

    textFont = pygame.font.Font(Constants.FONT_STYLE, Constants.DEFAULT_FONT_SIZE)
    textSurface = textFont.render(text, True, Constants.BLACK)

    textRectangle = textSurface.get_rect() 
    textRectangle.left = xPostion
    textRectangle.top = yPosition

    window.blit(textSurface, textRectangle)

def decreaseClockRate(delay, step):

    return delay + step

def increaseClockRate(delay, step):

    if delay > 0:
        return delay - step
    else:
        return delay


def reset(automaton):

    if automaton != None:
        automaton.resetGrids()
        automaton.drawGrid()

def checkButtons(mousePosition, buttonPositions, buttonDimensions):

    overButton = 0

    if len(buttonPositions) == 4:
        if onButton(mousePosition, buttonPositions[0], buttonDimensions):
            overButton = Constants.START_BUTTON
        elif onButton(mousePosition, buttonPositions[1], buttonDimensions):
            overButton = Constants.STOP_BUTTON
        elif onButton(mousePosition, buttonPositions[2], buttonDimensions):
            overButton = Constants.FASTER_BUTTON
        elif onButton(mousePosition, buttonPositions[3], buttonDimensions):
            overButton = Constants.SLOWER_BUTTON

    return overButton

def onButton(mousePosition, buttonPosition, buttonDimensions):

    xInside = False
    yInside = False    

    if mousePosition[0] > buttonPosition[0] and mousePosition[0] < (buttonPosition[0] + buttonDimensions[0]):
        xInside = True
    
    if mousePosition[1] > buttonPosition[1] and mousePosition[1] < (buttonPosition[1] + buttonDimensions[1]):
        yInside = True

    if xInside and yInside:
        return True
    else:
        return False


# Setup

pygame.init()
window = pygame.display.set_mode((Constants.WINDOW_WIDTH, Constants.WINDOW_LENGTH))

cells = []
globalClock = Constants.DEFAULT_DELAY

liveCell = pygame.image.load("alive.png").convert_alpha()
deadCell = pygame.image.load("dead.png").convert_alpha()
button = pygame.image.load("button.png").convert_alpha()

buttonDimensions = (button.get_width(), button.get_height())

buttonPositions = []

buttonPositions.append(Constants.START_BUTTON_LOCATION)
buttonPositions.append(Constants.STOP_BUTTON_LOCATION)
buttonPositions.append(Constants.FASTER_BUTTON_LOCATION)
buttonPositions.append(Constants.SLOWER_BUTTON_LOCATION)


for index in range(0, Constants.TOTAL_INDICES):
    cells.append(False)
    
    window.blit(liveCell, ((index % Constants.GRID_SIZE) * Constants.ROOT_SIZE, 
        (index / Constants.GRID_SIZE) * Constants.ROOT_SIZE))

pygame.draw.rect(window, Constants.GREY, Constants.BUTTON_BOX_LOCATION)

window.blit(button, Constants.START_BUTTON_LOCATION)
window.blit(button, Constants.STOP_BUTTON_LOCATION)
window.blit(button, Constants.FASTER_BUTTON_LOCATION)
window.blit(button, Constants.SLOWER_BUTTON_LOCATION)

drawText(Constants.START_LABEL, 45, 535)
drawText(Constants.STOP_LABEL, 175, 535)
drawText(Constants.FASTER_LABEL, 297, 535)
drawText(Constants.SLOWER_LABEL, 422, 535)

automaton = Automaton.Automaton(window, Constants.TOTAL_INDICES)
automaton.setImages([liveCell, deadCell])

run = False

# Main loop

while True:
    
    automaton.drawGrid()
    pygame.display.flip()
    xPosition, yPosition = pygame.mouse.get_pos()

    overButton = checkButtons((xPosition, yPosition), buttonPositions, buttonDimensions)

    for event in pygame.event.get():

        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            
            if not run:
                automaton.setCell((xPosition, yPosition))

            if overButton == Constants.START_BUTTON:
                run = True
            if overButton == Constants.STOP_BUTTON:
                run = False
            if overButton == Constants.FASTER_BUTTON:
                Constants.DEFAULT_DELAY = increaseClockRate(Constants.DEFAULT_DELAY, Constants.DELAY_STEP)
            if overButton == Constants.SLOWER_BUTTON:
                Constants.DEFAULT_DELAY = decreaseClockRate(Constants.DEFAULT_DELAY, Constants.DELAY_STEP)

            
        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()



    if run:
        automaton.updateGrid()
        sleep(Constants.DEFAULT_DELAY)
        print("!!!")