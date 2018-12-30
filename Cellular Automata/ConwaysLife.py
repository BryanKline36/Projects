
import pygame
import constants
from math import sqrt
from time import sleep

# CellGrid class definition

class CellGrid:

    grid = None
    gridSize = None
    offset = None
    current = None
    dead = None
    alive = None

    def __init__(self, size):

        self.grid = []            
        self.gridSize = int(size)
        self.offset = int(sqrt(size))
        self.current = False
        self.dead = False
        self.alive = True

        for index in range(0, self.gridSize):
            self.grid.append(self.dead)

    def clearGrid(self):

        for index in range(0, self.gridSize):
            self.grid[index] = self.dead

    def setCurrent(self, current):

        self.current = current

    def toggleCell(self, index):

        if index >= 0 and index < self.gridSize:
            self.grid[index] = self.grid[index] ^ True

    def getNeighborIndices(self, index):

        neighborIndices = []
        neighbors = [(index - self.offset - 1), (index - self.offset), (index - self.offset + 1), 
                    (index - 1), index, (index + 1), 
                    (index + self.offset - 1), (index + self.offset), (index + self.offset + 1)]

        if index >= 0 and index < self.gridSize:
            for position in neighbors:
                if position >= 0 and position < self.gridSize:
                    neighborIndices.append(position)

        return neighborIndices

    def getLiveNeighborCount(self, index):

        liveNeighbors = 0

        if index >= 0 and index < self.gridSize:
            neighborIndices = self.getNeighborIndices(index)

            for neighborIndex in neighborIndices:
                if self.grid[neighborIndex]:
                    liveNeighbors += 1

        return liveNeighbors

    def applyRules(self, index):

        state = None

        if index >= 0 and index < self.gridSize:
            neighborCount = self.getLiveNeighborCount(index)
            
            if self.grid[index] and (neighborCount < 2 or neighborCount > 3):
                state = self.dead

            if (not self.grid[index]) and (neighborCount > 1 and neighborCount < 4):
                state = self.alive

        return state

    def printGrid(self):

        print("Grid Start:")
        
        for index in range(0, self.gridSize):
            print(self.grid[index])
        
        print("Grid End")    

# Automaton class definition

class Automaton:

    window = None
    grids = None
    currentGridIndex = None
    gridSize = None
    cellSize = None
    aliveImage = None
    deadImage = None

    def __init__(self, window, size):

        self.window = window
        self.grids = []
        self.grids.append(CellGrid(size))
        self.grids.append(CellGrid(size))
        print(self.grids)
        self.grids[0].setCurrent(True)
        self.grids[1].setCurrent(False)
        self.currentGridIndex = 0
        self.gridSize = size
        self.gridSide = int(sqrt(self.gridSize))
        self.cellSize = int(sqrt(self.gridSide))

    def setImages(self, paths):

        if len(paths) == 2:
            self.aliveImage = paths[0]
            self.deadImage = paths[1]


    def getCurrentGrid(self):

        if self.grids[0].current and not self.grids[1].current:
            self.currentGridIndex = 0 
        elif not self.grids[0].current and self.grids[1].current:
            self.currentGridIndex = 1

    def setCurrentGrid(self, index):
        # self.printGrids()
        print(self.grids)
        self.grids[1].printGrid()
        if index >= 0 and index < 2:
            self.currentGridIndex = index
            self.grids[1].setCurrent(True)    
            self.grids[index ^ 1].setCurrent(False)    

    def updateGrid(self):
        
        self.getCurrentGrid()

        for index in range(0, self.gridSize):
            self.grids[self.currentGridIndex ^ 1] = self.grids[self.currentGridIndex].applyRules(index) 


        self.grids[self.currentGridIndex].clearGrid()  
        self.setCurrentGrid(self.currentGridIndex ^ 1) 

    def drawGrid(self):

        if self.window != None:
            for index in range(0, self.gridSize):
                xPosition = (index % self.gridSide) * self.cellSize
                yPosition = (index / self.gridSide) * self.cellSize

                if self.grids[self.currentGridIndex].grid[index]:
                    image = self.aliveImage
                else:
                    image = self.deadImage

                self.window.blit(image, (xPosition, yPosition))

    def setCell(self, position):

        xPosition = position[0] / self.cellSize
        yPosition = position[1] / self.cellSize

        index = (xPosition + (yPosition * self.gridSide))

        # print(index)

        self.grids[self.currentGridIndex].toggleCell(index)

    def resetGrids(self):

        self.grids[0].clearGrid()
        self.grids[1].clearGrid()

    def printGrids(self):

        self.grids[0].printGrid()
        self.grids[1].printGrid()

# Free functions

def drawText(text, xPostion, yPosition):

    textFont = pygame.font.Font(constants.FONT_STYLE, constants.DEFAULT_FONT_SIZE)
    textSurface = textFont.render(text, True, constants.BLACK)

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


# Setup

pygame.init()
window = pygame.display.set_mode((constants.WINDOW_WIDTH, constants.WINDOW_LENGTH))

cells = []
globalClock = constants.DEFAULT_DELAY

liveCell = pygame.image.load("alive.png").convert_alpha()
deadCell = pygame.image.load("dead.png").convert_alpha()
button = pygame.image.load("button.png").convert_alpha()

for index in range(0, constants.TOTAL_INDICES):
    cells.append(False)
    
    window.blit(liveCell, ((index % constants.GRID_SIZE) * constants.ROOT_SIZE, 
        (index / constants.GRID_SIZE) * constants.ROOT_SIZE))

pygame.draw.rect(window, constants.GREY, constants.BUTTON_BOX_LOCATION)

window.blit(button, constants.START_BUTTON)
window.blit(button, constants.STOP_BUTTON)
window.blit(button, constants.FASTER_BUTTON)
window.blit(button, constants.SLOWER_BUTTON)

drawText(constants.START_LABEL, 45, 535)
drawText(constants.STOP_LABEL, 175, 535)
drawText(constants.FASTER_LABEL, 297, 535)
drawText(constants.SLOWER_LABEL, 422, 535)

automaton = Automaton(window, constants.TOTAL_INDICES)
automaton.setImages([liveCell, deadCell])
# automaton.printGrids()


# Main loop

while True:
    
    automaton.drawGrid()
    pygame.display.flip()
    xPosition, yPosition = pygame.mouse.get_pos()

    for event in pygame.event.get():

        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            automaton.setCell((xPosition, yPosition))
            
        if event.type == pygame.QUIT:
            
            pygame.quit()
            exit()


    automaton.updateGrid()
    sleep(1)