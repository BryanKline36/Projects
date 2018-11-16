
# File name: 	CyberSecurityWebScraper.py
# Author: 		Nathanael Fuller
# Author: 		Bryan Kline
# Class:		CS445
# Date:			May 3, 2018
# Description:	Main driver implementation file (Python)

from WebScraper import WebScraper
from Filter import Filter
from TemporaryDatabase import TemporaryDatabase
from Clear import Clear
from time import sleep
import subprocess
import sys

deleteAll = False
deleteDatabase = False
deleteTemporaryDatabase = True
deleteCSV = False

# command line arguments are inspected to determined whether or not the string 'delete' is present, if so 
# the database, temporary database, and CSV file are deleted, by default only the temporary database and
# CSV file are deleted
if len(sys.argv) > 1 and sys.argv[1].lower() == "delete":
	deleteAll = True

if deleteAll:
	deleteDatabase = True
	deleteTemporaryDatabase = True
	deleteCSV = True

# systemInitialization.py script run in order to create SQLite database and compile C++ code if necessary  
subprocess.call(["python3", "systemInitialization.py"])

# program information display
print("\nCyber Security Webscraper")
print("CS445 UNR, Spring 2018")
print("Authors: Nathanael Fuller, Bryan Kline\n")
print("Establishing connections with websites and scraping their content takes some time, please wait.")
print("working...", end="")
print(".", end="")

# web site content scraped with WebScraper class object 
webScraper = WebScraper()
webScraper.run()

print(".", end="")

# scraped content filtered with Filter class object
filter = Filter()
filter.run()

print(".", end="")

# temporary database text file created for C++ program to use with TemporaryDatabase class object
temporaryDatabase = TemporaryDatabase()
temporaryDatabase.run()

print(".", end="")

# C++ program executed to update the dictionary
subprocess.call(["./updateDictionary"])	

print(".", end="")

# files created by the program cleared with Clear class object
clear = Clear(deleteDatabase, deleteTemporaryDatabase, deleteCSV)
clear.cleanUp()

print(".")
