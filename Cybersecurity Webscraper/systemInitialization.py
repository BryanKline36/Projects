
# File name: 	systemInitialization.py
# Author: 		Nathanael Fuller
# Author: 		Bryan Kline
# Class:		CS445
# Date:			May 3, 2018
# Description:	Script to build and initialize the system (Python)

import sqlite3
import subprocess


# the contents of the current working working directory are inspected to determined whether or not the
# database already exists and whether or not the C++ program to dynamically update the dictionary has
# been built

directoryContents = subprocess.Popen('ls', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

databaseExists = False
dictionaryExists = False
accumulatorExists = False
databaseName = "securityHeadlines.db"
dictionaryName = "Dictionary.o"
accumulatorName = "Accumulator.o"

for item in directoryContents.stdout.readlines():
    string = item.decode()
    string = string[:-1]  
    if string == databaseName:
    	databaseExists = True
    if string == dictionaryName:
    	dictionaryExists = True
    if string == accumulatorName:
    	accumulatorExists = True	

# if the database does not exist it is created 
if not databaseExists:

	database = sqlite3.connect('securityHeadlines.db')

	database.execute('''CREATE TABLE HEADLINES
	         (ID 			INT 	PRIMARY KEY,
	         HEADLINE       TEXT,
	         URL            TEXT,
	         TIMEDATE       TEXT,
	         SCORE			INT);''')

	database.close()

# if the C++ program which updates the dictionary has not been built then it is compiled by way of a makefile
if not dictionaryExists and not accumulatorExists:
	subprocess.call(["make"])	
