
# File name: 	TemporaryDatabase.py
# Author: 		Nathanael Fuller
# Author: 		Bryan Kline
# Class:		CS445
# Date:			May 3, 2018
# Description:	TemporaryDatabase class implementation file (Python)

import subprocess
import sqlite3
import time

class TemporaryDatabase:

	# TemporaryDatabase class constants

	__outFileDatabase = None

	__databaseName = "securityHeadlines.db"
	__tempDatabaseName = "tempDatabase.txt"

	__databaseContents = []

	# Name:			__init__				
	# Description:	TemporaryDatabase class default constructor which creates the temporary database file
	#				to write to
	# Parameters:	None
	# Return:		None
	def __init__(self):
		
		self.__outFileDatabase = open(self.__tempDatabaseName, "w")

	# Name:			readInDatabase			
	# Description:	TemporaryDatabase class method which opens a connection with the SQLite database and reads its
	#				contents into a local data structure
	# Parameters:	None
	# Return:		None
	def readInDatabase(self):
	
		self.__databaseConnection = sqlite3.connect(self.__databaseName)

		query = self.__databaseConnection.cursor()
		query.execute("SELECT HEADLINE FROM HEADLINES")

		queryItem = query.fetchall()

		for line in queryItem:
			self.__databaseContents.append(line[0])

		self.__databaseConnection.close()	

	# Name:			writeOutDatabase			
	# Description:	TemporaryDatabase class method which moves through the class data structure which holds the
	#				contents of the database and writes them to a file
	# Parameters:	None
	# Return:		None
	def writeOutDatabase(self):
	
		for line in self.__databaseContents:
			self.__outFileDatabase.write(line)
			self.__outFileDatabase.write("\n")

		self.__outFileDatabase.close()	

	# Name:			run			
	# Description:	TemporaryDatabase class method which acts as the main interface through which the class 
	#				methods are accessed which reads in the database and writes its contents to a raw file
	# Parameters:	None
	# Return:		None
	def run(self):
	
		self.readInDatabase()
		self.writeOutDatabase()

