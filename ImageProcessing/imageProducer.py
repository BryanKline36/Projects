

def initialize(image):

	global row
	global column

	i = 0
	while i < row:
		j = 0
		while j < column:
			image[i][j] = 0
			j += 1
		i += 1	

def readInFile(image):

	global row
	global column

	fileName = "lenna.pgm"
	file = open(fileName, "r")

	i = 0
	for line in file:
		j = 0
		for value in line:
			# image[i][j] = int(value)
			print(value)
			i +=1
		j += 1
		
		
def changeIntensity(image, intensity):

	global row
	global column

	i = 0
	while i < row:
		j = 0
		while j < column:
			
			image[i][j] += intensity

			j += 1	
		i += 1	


def writeToFile(image):

	global row
	global column

	fileName = "outputImage.pgm"
	file = open(fileName, "w")

	i = 0
	while i < row:
		j = 0
		while j < column:
			file.write(str(image[i][j]))
			file.write(" ")
			j += 1
		file.write('\n')	
		i += 1		


def writeRows(image, rowLocation, intensity):

	global row

	i = 0
	while i < row:
		image[rowLocation][i] = intensity
		i += 1

def writeColumns(image, columnLocation, intensity):

	global column

	i = 0
	while i < column:
		image[i][columnLocation] = intensity
		i += 1



fileName = "myTestImage.pgm"
file = open(fileName, "w")

global row
global row

row = 255
column = 255


image = [[0 for x in range(column)] for y in range(row)]




file.write("P2\n")
file.write(str(row) + " " + str(column) + "\n")
file.write("255\n")

initialize(image)

readInFile(image)

# writeRows(image, 16, 255)
# writeRows(image, 32, 128)

# writeColumns(image, 32, 200)
# writeColumns(image, 50, 64)

writeToFile(image)
file.close()	