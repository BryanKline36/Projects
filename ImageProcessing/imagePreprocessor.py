
import sys
import numpy  
from PIL import Image 

# Name:			normalize
# Description:	Function which takes in a 2D Numpy float array with values from 0 to 255 and normalizes
# 				the data to values between 0 and 1
# Parameters:	Takes in a Numpy array which is the image pixel values converted to floats, as well
# 				as the image height and width
# Return:		Returns the normalized float array
def normalize(array, height, width):

	for row in range(height):
		for column in range(width):
			array[row][column] = array[row][column] / 255;

	return array		

# Name:			openImage
# Description:	Function which checks that an image file name is provided as a command line argument,
# 				opens the image, converts the image to grayscale, and returns it
# Parameters:	Takes in a string array, sys.argv, which is the command line arguments 
# Return:		Returns the opened image after it has been converted to grayscale
def openImage(commandLine):

	if len(commandLine) > 1:

		fileName = commandLine[1]
		originalImage = Image.open(fileName) 
		image = originalImage.convert('L')

		return image

	else:	

		return None	

# Name:			commandLineOptions
# Description:	Function which inspects the command line arguments for flags "-s" for "show" and
# 				"-r" for "raw" to show the image being converted to a normalized float array and
# 				to print the raw values to terminal
# Parameters:	Takes in a string array, sys.argv, which is the command line arguments, the image,
# 				the image height and width, and the array with the raw values
# Return:		None
def commandLineOptions(commandLine, image, height, width, array):

	if len(commandLine) > 3 and commandLine[3] == "-s":

		image.show()

	if len(commandLine) > 4 and commandLine[4] == "-r":

		for row in range(height):
			for column in range(width):
				print(array[row][column])


# Name:			saveData
# Description:	Function which takes the third command line argument for the name of the file to write the
# 				output to, if there is no such command line argument then the name is defaulted to "output",
#				and the normalized float array is iterated through and written to the file, comma delimited
# Parameters:	Takes in the normalized float array from the image, the height and width of the image, and
# 				string array, sys.argv, which is the command line arguments
# Return:		None
def saveData(normalizedArray, height, width, commandLine):
	
	if len(commandLine) > 2:

		fileName = commandLine[2]

	else:

		fileName = "output"

	file = open(fileName, "w")
	
	for row in range(height):
		for column in range(width):
			file.write(str(round(normalizedArray[row][column], 3)) + ", ")
		file.write('\n')	

	file.close()		 		


if __name__ == '__main__':

	# open and convert the image
	image = openImage(sys.argv)

	# if the image name was provided as a command line argument
	if not image == None:

		width, height = image.size 

		# convert the image into a Numpy float array
		imageArray = numpy.array(image)
		imageArray = imageArray.astype(float)

		# normalize the data in the float array to values between 0 and 1 
		normalizedArray = normalize(imageArray, height, width)

		# save the data to a file
		saveData(normalizedArray, height, width, sys.argv)

		# check for command line flags to show the image and/or print the raw data to the screen
		commandLineOptions(sys.argv, image, height, width, normalizedArray)

	# no file name provided 
	else:

		print("Error: no image supplied.  Enter the image file name as a command line argument.")		

	
