
import pygame
import Constants
import Automaton
from math import sqrt
from time import sleep

# # CellGrid class definition

# class CellGrid:

#     grid = None
#     gridSize = None
#     offset = None
#     current = None
#     dead = None
#     alive = None

#     def __init__(self, size):

#         self.grid = []            
#         self.gridSize = int(size)
#         self.offset = int(sqrt(size))
#         self.current = False
#         self.dead = False
#         self.alive = True

#         for index in range(0, self.gridSize):
#             self.grid.append(self.dead)

#     def clearGrid(self):

#         for index in range(0, self.gridSize):
#             self.grid[index] = self.dead

#     def setCurrent(self, current):

#         self.current = current

#     def toggleCell(self, index):

#         if index >= 0 and index < self.gridSize:
#             self.grid[index] = self.grid[index] ^ True

#     def getNeighborIndices(self, index):

#         neighborIndices = []
#         neighbors = [(index - self.offset - 1), (index - self.offset), (index - self.offset + 1), 
#                     (index - 1), index, (index + 1), 
#                     (index + self.offset - 1), (index + self.offset), (index + self.offset + 1)]

#         if index >= 0 and index < self.gridSize:
#             for position in neighbors:
#                 if position >= 0 and position < self.gridSize:
#                     neighborIndices.append(position)

#         return neighborIndices

#     def getLiveNeighborCount(self, index):

#         liveNeighbors = 0

#         if index >= 0 and index < self.gridSize:
#             neighborIndices = self.getNeighborIndices(index)

#             for neighborIndex in neighborIndices:
#                 if self.grid[neighborIndex]:
#                     liveNeighbors += 1

#         return liveNeighbors

#     def applyRules(self, index):

#         state = False

#         if index >= 0 and index < self.gridSize:
#             neighborCount = self.getLiveNeighborCount(index)
            
#             if self.grid[index] and (neighborCount < 2 or neighborCount > 3):
#                 state = self.dead

#             if (not self.grid[index]) and (neighborCount > 1 and neighborCount < 4):
#                 state = self.alive

#         return state

#     def setCellState(self, index, state):

#         self.grid[index] = state

#     def printGrid(self):

#         print("Grid Start:")
        
#         for index in range(0, self.gridSize):
#             print(self.grid[index])
        
#         print("Grid End")    

# # Automaton class definition

# class Automaton:

#     window = None
#     grids = None
#     currentGridIndex = None
#     gridSize = None
#     cellSize = None
#     aliveImage = None
#     deadImage = None

#     def __init__(self, window, size):

#         self.window = window
#         self.grids = []
#         self.grids.append(CellGrid(size))
#         self.grids.append(CellGrid(size))
#         self.grids[0].setCurrent(True)
#         self.grids[1].setCurrent(False)
#         self.currentGridIndex = 0
#         self.gridSize = size
#         self.gridSide = int(sqrt(self.gridSize))
#         self.cellSize = int(sqrt(self.gridSide))

#     def setImages(self, paths):

#         if len(paths) == 2:
#             self.aliveImage = paths[0]
#             self.deadImage = paths[1]


#     def getCurrentGrid(self):

#         if self.grids[0].current and not self.grids[1].current:
#             self.currentGridIndex = 0 
#         elif not self.grids[0].current and self.grids[1].current:
#             self.currentGridIndex = 1

#     def setCurrentGrid(self, index):
#         if index >= 0 and index < 2:
#             self.currentGridIndex = index
#             self.grids[index].setCurrent(True)    
#             self.grids[index ^ 1].setCurrent(False)    

#     def updateGrid(self):
        
#         self.getCurrentGrid()
#         for index in range(0, self.gridSize):
#             print(self.currentGridIndex ^ 1)
#             self.grids[self.currentGridIndex ^ 1].setCellState(index, self.grids[self.currentGridIndex].applyRules(index)) 

#         self.grids[self.currentGridIndex].clearGrid()  
#         self.setCurrentGrid(self.currentGridIndex ^ 1)

#     def drawGrid(self):

#         if self.window != None:
#             for index in range(0, self.gridSize):
#                 xPosition = (index % self.gridSide) * self.cellSize
#                 yPosition = (index / self.gridSide) * self.cellSize

#                 if self.grids[self.currentGridIndex].grid[index]:
#                     image = self.aliveImage
#                 else:
#                     image = self.deadImage

#                 self.window.blit(image, (xPosition, yPosition))

#     def setCell(self, position):

#         xPosition = position[0] / self.cellSize
#         yPosition = position[1] / self.cellSize

#         index = (xPosition + (yPosition * self.gridSide))

#         self.grids[self.currentGridIndex].toggleCell(index)

#     def resetGrids(self):

#         self.grids[0].clearGrid()
#         self.grids[1].clearGrid()

#     def printGrids(self):

#         self.grids[0].printGrid()
#         self.grids[1].printGrid()

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

print(buttonPositions)
print(buttonDimensions)

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


# Main loop

while True:
    
    automaton.drawGrid()
    pygame.display.flip()
    xPosition, yPosition = pygame.mouse.get_pos()

    overButton = checkButtons((xPosition, yPosition), buttonPositions, buttonDimensions)

    for event in pygame.event.get():

        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            automaton.setCell((xPosition, yPosition))

            if overButton == Constants.START_BUTTON:
                print("start")
            if overButton == Constants.STOP_BUTTON:
                print("stop")
            if overButton == Constants.FASTER_BUTTON:
                print("faster")
            if overButton == Constants.SLOWER_BUTTON:
                print("slower")

            
        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()


    # automaton.updateGrid()
    # sleep(1)