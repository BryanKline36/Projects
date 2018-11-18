


# Training Data Note:
# 1455 training images
# 20 non-apple from each folder, take 35 more from last folder

import os
import subprocess
import sys

# set file name and check command line argument for image prefix, defaulting "apple"  
FILE_NAME = "rename.py"

if len(sys.argv) > 1:

    PREFIX = sys.argv[1]
    
else:

    PREFIX = "apple"


# Name:         getDirectoryList
# Description:  Function which issues a system call to "ls", either in the parent directory or in a 
#               child directory, which is passed in as a parameter, and returns the contents of the 
#               directory
# Parameters:   Takes in the directory name as a string
# Return:       Returns a subpropcess object which is the contents of the directory
def getDirectoryList(directory):

    if directory == None:

        directoryPath = "ls"
    else:    

        directoryPath = "ls " + directory
    
    directoryContents = subprocess.Popen(directoryPath, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    return directoryContents

# Name:         createDirectoryList
# Description:  Function which iterates through a subpropcess object containing the contents of a directory
#               and returns it as a formatted list 
# Parameters:   Takes in a subpropcess object which is the contents of a directory
# Return:       Returns the contents of a directory as a list 
def createDirectoryList(directories):

    directoryList = []

    for directory in directories.stdout.readlines():

        directory = directory[:-1]
        directoryList.append(directory)

    return directoryList    


fileNumber = 0
folderNumber = 0

# create a list of all directories 
directories = getDirectoryList(None)
directoryList = createDirectoryList(directories)

# iterate through the folders in the list of directories
for folder in range(len(directoryList)):
    
    # in each directory, get a list of the files in it
    directory = getDirectoryList(directoryList[folder])
    
    # if the file is not this current file, "rename.py", then build the old name, a new name, and
    # rename the file such that all files adhere to a particular naming convention, in this case
    # files are named "apple_" or "nonapple_" followed by their number  
    if directoryList[folder] != FILE_NAME:

        for file in directory.stdout.readlines():
            
            fileName = file[:-1]

            oldName = directoryList[folder] + "/" + fileName
            newName = directoryList[folder] + "/" + PREFIX + "_" + str(folderNumber) + ".jpg"
            
            os.rename(oldName, newName)

            folderNumber += 1


