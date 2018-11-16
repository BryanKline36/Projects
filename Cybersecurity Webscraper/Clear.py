
# File name: 	Clear.py
# Author: 		Nathanael Fuller
# Author: 		Bryan Kline
# Class:		CS445
# Date:			May 3, 2018
# Description:	Clear class implementation file (Python)

import subprocess

class Clear:

	# Clear class constants

	__deleteDatabase = False
	__deleteTempDatabase = False
	__deleteCSV = False

	# Name:			__init__			
	# Description:	Clear class parameterized constructor
	# Parameters:	Takes in bools corresponding to whether the database, temporary database, and CSV file
	#				should be deleted upon termination of the program
	# Return:		None	
	def __init__(self, database, tempDatabase, CSV):
		
		self.__deleteDatabase = database
		self.__deleteTempDatabase = tempDatabase
		self.__deleteCSV = CSV

	# Name:			cleanUp			
	# Description:	Clear class method which checks the class data members to determine if the database,
	#				temporary database, and CSV file should be deleted upon termination of the program
	# Parameters:	None
	# Return:		None
	def cleanUp(self):	
		
		if self.__deleteDatabase:
			self.deleteDatabase()

		if self.__deleteTempDatabase:
			self.deleteTempDatabase()

		if self.__deleteCSV:
			self.deleteCSV()	

	# Name:			deleteDatabase			
	# Description:	Clear class method which deletes the database from the current working directory
	# Parameters:	None
	# Return:		None
	def deleteDatabase(self):	

		subprocess.call(["rm", "securityHeadlines.db"])

	# Name:			deleteTempDatabase			
	# Description:	Clear class method which deletes the temporary database from the current working directory
	# Parameters:	None
	# Return:		None
	def deleteTempDatabase(self):	

		subprocess.call(["rm", "tempDatabase.txt"])
	
	# Name:			deleteCSV			
	# Description:	Clear class method which deletes the CSV file from the current working directory
	# Parameters:	None
	# Return:		None
	def deleteCSV(self):	

		subprocess.call(["rm", "securityHeadlines.csv"])
