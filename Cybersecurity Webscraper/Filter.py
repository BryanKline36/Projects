
# File name: 	Filter.py
# Author: 		Nathanael Fuller
# Author: 		Bryan Kline
# Class:		CS445
# Date:			May 3, 2018
# Description:	Filter class implementation file (Python)

from threading import Thread
import sqlite3

class Headline:

	# Headling class constants

	__primaryKey = 0
	__headline = ""
	__URL = ""
	__timeDate = ""
	score = 0

	# Name:			__init__			
	# Description:	Headline class parameterized constructor which builds a Headline object from the parameters
	#				passed in 
	# Parameters:	Takes in ints corresponding to the primary key and score and strings corresponding to the
	#				headline, URL, and time stamp 
	# Return:		None
	def __init__(self, key, headline, URL, timeDate, score):

		self.__primaryKey = key
		self.__headline = headline
		self.__URL = URL
		self.__timeDate = timeDate
		self.score = score

	# Name:			getPrimaryKey			
	# Description:	Headline class method which returns the primary key
	# Parameters:	None
	# Return:		Returns the primary key
	def getPrimaryKey(self):

		return self.__primaryKey	
		
	# Name:			getHeadline			
	# Description:	Headline class method which returns the headline
	# Parameters:	None
	# Return:		Returns the headline	
	def getHeadline(self):

		return self.__headline

	# Name:			getURL			
	# Description:	Headline class method which returns the URL
	# Parameters:	None
	# Return:		Returns the URL
	def getURL(self):

		return self.__URL

	# Name:			getTimeDate			
	# Description:	Headline class method which returns the time stamp
	# Parameters:	None
	# Return:		Returns the time stamp
	def getTimeDate(self):

		return self.__timeDate

	# Name:			getScore			
	# Description:	Headline class method which returns the score
	# Parameters:	None
	# Return:		Returns the score
	def getScore(self):	

		return self.score

	# Name:			setPrimaryKey			
	# Description:	Headline class method which sets the primary key
	# Parameters:	Takes in a primary key which will be assinged to the corresponding class data member 
	# Return:		None
	def setPrimaryKey(self, key):
		
		self.__primaryKey = key		

	# Name:			printHeadlineObject			
	# Description:	Headline class method which prints the class data members 
	# Parameters:	None
	# Return:		None
	def printHeadlineObject(self):
	
		print("Primary Key: " + str(self.__primaryKey))
		print("Headline: " + self.__headline)
		print("URL: " + self.__URL)
		print("Time and Date: " + self.__timeDate,  end="")
		print("Score: " + str(self.score) + "\n")	
		
class Filter:

	# Filter class constants

	__inFileCSV = None
	__inFileDictionary = None
	__CSVFileName = "securityHeadlines.csv"
	__dictionaryName = "dictionary.txt"
	__databaseName = "securityHeadlines.db"
	__CSVContents = []
	__dictionaryContents = []
	__matches = []
	__sortedMatches = []
	__databaseContents = []
	__CSVSize = 0
	__dictionarySize = 0
	__lastKey = 0
	__databaseEmpty = True

	# Name:			__init__			
	# Description:	Filter class default constructor which opens the CSV and dictionary files
	# Parameters:	None
	# Return:		None
	def __init__(self):

		self.__inFileCSV = open(self.__CSVFileName, "r")
		self.__inFileDictionary = open(self.__dictionaryName, "r")

	# Name:			databaseCommit				
	# Description:	Filter class method which takes in a Headline object, gets its data members, opens a
	#			 	connection with the SQLite databsse	and pushes the data from the object into the database
	# Parameters:	Takes in a Headline object and a bool corresponding to whether or not the class should
	# 				print tje object for diagnostic purposes 
	# Return:		None
	def databaseCommit(self, headlineObject, verbose):

		key = headlineObject.getPrimaryKey()
		headline = headlineObject.getHeadline()
		URL = headlineObject.getURL()
		timeDate = headlineObject.getTimeDate()
		score = headlineObject.getScore()

		if verbose:
			headlineObject.printHeadlineObject()

		self.__databaseConnection = sqlite3.connect(self.__databaseName)
		self.__databaseConnection.execute("INSERT INTO HEADLINES (ID,HEADLINE,URL,TIMEDATE,SCORE) VALUES (?, ?, ?, ?, ?);", (key, headline, URL, timeDate, score))
		self.__databaseConnection.commit()
		self.__databaseConnection.close()

	# Name:			readInDatabase			
	# Description:	Filter class method which opens a connection with the SQLite database, reads in all the data
	#				from it from previous passes into a data structure if there are any entries in the database 
	# Parameters:	None
	# Return:		None
	def readInDatabase(self):
	
		self.__databaseConnection = sqlite3.connect(self.__databaseName)

		query = self.__databaseConnection.cursor()
		query.execute("SELECT HEADLINE FROM HEADLINES")

		queryItems = query.fetchall()

		for line in queryItems:
			self.__databaseContents.append(line[0])

		if len(self.__databaseContents) == 0:
			self.__databaseEmpty = True
		else:
			self.__databaseEmpty = False		

		self.__databaseConnection.close()	

	# Name:			getLastPrimaryKey			
	# Description:	Filter class method which opens a connection with the SQLite database and gets the
	#				primary key from the last entry in it if there are any so as to start the data it
	#				pushes into the database on the current pass from the correct primary key 
	# Parameters:	None
	# Return:		None
	def getLastPrimaryKey(self):
		
		lastKey = 0

		self.__databaseConnection = sqlite3.connect(self.__databaseName)

		query = self.__databaseConnection.cursor()
		query.execute("SELECT ID FROM HEADLINES")

		primaryKeys = query.fetchall()

		if len(primaryKeys) > 0:
			lastKey = len(primaryKeys)

		self.__databaseConnection.close()

		self.__lastKey = lastKey

	# Name:			readFileContents			
	# Description:	Filter class method which opens the CSV file holding the raw data from the site scraped, 
	#				reads the contents into a class data structure and makes each item lower case
	# Parameters:	None
	# Return:		None
	def readFileContents(self):

		for line in self.__inFileCSV:
			line = line.split(",")
			for item in line:
				self.__CSVContents.append(item.lower())
				self.__CSVSize += 1

		self.__CSVSize = int(self.__CSVSize / 3)

		self.__inFileCSV.close()

	# Name:			readDictionary			
	# Description:	Filter class method which opens the dictionary file and reads in its contents into a class
	#				data structure
	# Parameters:	None
	# Return:		None
	def readDictionary(self):

		for line in self.__inFileDictionary:
			self.__dictionaryContents.append(line[:-1].lower())
			self.__dictionarySize += 1	

		self.__inFileDictionary.close()	

	# Name:			findMatches			
	# Description:	Filter class method which moves through the CSV file contents in the local data structure
	#				and checks each item against the contents of the dictionary data structure and if there is 
	#				a match then that item is added to a class data structure which keeps track of all scraped
	#				content with terms present that are found in the dictionary, also scores each item based 
	#				on the number of matches it has against the dictionary
	# Parameters:	None
	# Return:		None
	def findMatches(self):
	
		headlineObject = None

		index = 0
		while index < self.__CSVSize * 3:

			itemScore = 0
			for entry in self.__dictionaryContents:
				itemScore += self.matchScore(self.__CSVContents[index], entry)

			if itemScore > 0:
				headlineObject = Headline(0, self.__CSVContents[index], self.__CSVContents[index + 1], self.__CSVContents[index + 2], itemScore)
				
				self.__matches.append(headlineObject)

			index += 3	 

	# Name:			filterMatches			
	# Description:	Filter class method which moves through all the matches found between the database contents
	#				and the dictionary and removes all duplicates to prevent repeated content in the database	
	# Parameters:	None
	# Return:		None
	def filterMatches(self):

		if not self.__databaseEmpty:
			tempList = []

			for match in self.__matches:
				for databaseItem in self.__databaseContents:
					if match.getHeadline() == databaseItem:
						tempList.append(match)

			for tempItem in tempList:
				for match in self.__matches:
					if tempItem.getHeadline() == match.getHeadline():
						self.__matches.remove(match)

	# Name:			removePunctuation			
	# Description:	Filter class method which takes in a string and returns the string with all punctuation
	#				removed
	# Parameters:	Takes in a string which is to have its punctuation removed
	# Return:		Returns the input string with all punctuation removed
	def removePunctuation(self, input):

		index = 0
		tempString = list(input)
		size = len(tempString)

		while index < size:
			if ord(tempString[index]) < 65 or (ord(tempString[index]) > 90 and ord(tempString[index]) < 97) or ord(tempString[index]) > 122:
				tempString[index] = ' '	
			index += 1

		input = "".join(tempString)

		return input

	# Name:			matchScore			
	# Description:	Filter class method which determines the total score for a headline based on the number of 
	#				matches it has in the dictionary
	# Parameters:	Takes in a headline and a dictionary term, splits the headline by white space to break it into 
	#				words, then steps through the words and checks them against the dictionary term to determine 
	#				the score for that headline 
	# Return:		Returns the score for the headline passed in as a parameter
	def matchScore(self, headline, dictionaryTerm):
	
		tempList = self.removePunctuation(headline)
		tempList = tempList.split(" ")
		score = 0

		for word in tempList:
			if word == dictionaryTerm:
				score += 1

		return score		

	# Name:			assignKeys			
	# Description:	Filter class method which determines the last primary key in the database and moves through 
	#				the sorted matches and assigns each one a primary key
	# Parameters:	None
	# Return:		None
	def assignKeys(self):	

		if not self.__lastKey == None:
			key = self.__lastKey
		else:
			key	= 0

		for match in self.__sortedMatches:
			match.setPrimaryKey(key)
			key += 1

	# Name:			orderMatches			
	# Description:	Filter class method which moves through the class data structure holding all the matches of
	#				headlines with the dictionary and sorts them by the score they received corresponding to the
	#				number of matches found
	# Parameters:	None
	# Return:		None
	def orderMatches(self):	

		self.__sortedMatches = sorted(self.__matches, key=lambda headlineObject: headlineObject.score, reverse=True)
		self.assignKeys()

	# Name:			commitMatches			
	# Description:	Filter class method which steps through the sorted matches and adds each one to the database
	# Parameters:	None
	# Return:		None
	def commitMatches(self):
	
		for match in self.__sortedMatches:
			self.databaseCommit(match, False)	

	# Name:			run			
	# Description:	Filter class method which acts as the primary interface for the class which opens separate
	#				threads to read in all files into local data structures and to find matches between the 
	#				scraped content and the dictionary, gets the next primary key to use, filters and sorts
	#				the matches, and pushes the matches into the database
	# Parameters:	None
	# Return:		None
	def run(self):

		readFileContentsThread = Thread(target=self.readFileContents)
		readDictionaryThread = Thread(target=self.readDictionary)
		findMatchesThread = Thread(target=self.findMatches)
		readInDatabaseThread = Thread(target=self.readInDatabase)

		readFileContentsThread.start()
		readDictionaryThread.start()
		findMatchesThread.start()
		readInDatabaseThread.start()

		readFileContentsThread.join()
		readDictionaryThread.join()
		findMatchesThread.join()
		readInDatabaseThread.join()

		getLastPrimaryKeyThread = Thread(target=self.getLastPrimaryKey)
		filterMatchesKeyThread = Thread(target=self.filterMatches)
		
		getLastPrimaryKeyThread.start()
		filterMatchesKeyThread.start()

		getLastPrimaryKeyThread.join()
		filterMatchesKeyThread.join()

		self.orderMatches()
		self.commitMatches()

	# Name:			printMatches			
	# Description:	Filter class method which prints all matches to the screen for diagnostic purposes
	# Parameters:	None
	# Return:		None
	def printMatches(self):

		for match in self.__sortedMatches:	
			match.printHeadlineObject()

		