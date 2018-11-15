
# File name: 	WebScraper.py
# Author: 		Nathanael Fuller
# Author: 		Bryan Kline
# Class:		CS445
# Date:			May 3, 2018
# Description:	WebScraper class implementation file (Python)

import bs4
from bs4 import BeautifulSoup
import urllib
from urllib.request import Request, urlopen
import time
import datetime
from threading import Thread

class WebScraper:

	# WebScraper class constants

	__outFile = None
	__CSVFileName = "securityHeadlines.csv"

	__USGovAnnouncementsURL = "https://www.us-cert.gov/announcements"
	__USGovAlertsURL = "https://www.us-cert.gov/ncas/alerts"
	__UKGovAlertsURL = "https://www.ncsc.gov.uk/index/alerts-and-advisories"
	__CanadaAlertsURL = "https://www.publicsafety.gc.ca/cnt/rsrcs/cybr-ctr/index-en.aspx#al"
	__reutersURL = "https://www.reuters.com/news/archive/cybersecurity"
	__securityAffairsURL = "http://securityaffairs.co/wordpress/"
	__hackerNewsURL = "https://thehackernews.com"
	__threatNewsURL = "https://threatpost.com/blog/"
	__computerWorldURL = "https://www.computerworld.com/category/security/"
	__techNewsWorldURL = "https://www.technewsworld.com/perl/section/tech-security"
	__darkReadingURL = "https://www.darkreading.com/attacks-breaches.asp"
	__hackerCombatURL = "https://hackercombat.com/"
	__SCMagazineURL = "https://www.scmagazine.com/news/section/6343/"
	__securityMagazineURL = "https://www.securitymagazine.com/topics/2236-cyber-security-news"
	__securityWeekURL = "https://www.securityweek.com/cybercrime"
	__redditURL = 'http://www.reddit.com/r/cybersecurity'


	# Name:			__init__
	# Description:	WebScraper class default constructor which opens the CSV file which the raw scraped
	# 				content is written to
	# Parameters:	None
	# Return:		None
	def __init__(self):

		self.__outFile = open(self.__CSVFileName, "w")

	# Name:			makeURLConnection
	# Description:	WebScraper class method which takes in the URL of a site to be scraped and recursively 
	# 				attempts to establish a connection with the site and returns the connection object 
	# Parameters:	Takes in a string which is the URL of the site to be connected to
	# Return:		Returns a connection object if a connection is established 	
	def makeURLConnection(self, url):

		try:
			return urlopen(url)
		except urllib.error.HTTPError:
			time.sleep(1)
			return self.makeURLConnection(url)

	# Name:			parseText
	# Description:	WebScraper class method which takes in a string and removes commas and semicolons
	# Parameters:	Takes in a string which has commas and semicolons removed from it
	# Return:		Returns the input string with commas and semicolons removed
	def parseText(self, input):

		temp = input.replace(",", "")
		output = temp.replace(";", "")

		return output

	# Name:			removeWhitespace
	# Description:	WebScraper class method which takes in a string and removes whitespace from it, including
	#				tabs, newlines, and carriage returns
	# Parameters:	Takes in a string to have whitespace removed from it
	# Return:		Returns the input string with whitespace removed
	def removeWhitespace(self, input):

		size = len(input)
		index = 0

		while index < size and (input[index] == ' ' or input[index] == '\t' or input[index] == '\r' or input[index] == '\n'):
			index += 1  

		output = input[index:]

		size = len(output) 
		index = len(output) - 1

		while index >= 0 and (output[index] == ' ' or output[index] == '\t' or output[index] == '\r' or output[index] == '\n'):
			index -= 1

		output = output[:-(size - index)]

		return output	

	# Name:			getTimeDate
	# Description:	WebScraper class method which gets the time and date and makes a time stamp from it
	# Parameters:	None
	# Return:		Returns a time stamp as a string 	
	def getTimeDate(self):

		now = datetime.datetime.now()
		timeString = str(now.hour) + ":" + str(now.minute) + ":" + str(now.second)
		dayString = str(now.month) + "/" + str(now.day) + "/" + str(now.year)	
		timeDayString = timeString + " " + dayString

		return timeDayString

	# Name:			pushRawHeadline
	# Description:	WebScraper class method which takes in strings which are the headline, URL, and time
	#				stamp and writes them to the CSV file which holds the raw scraped content
	# Parameters:	Takes in strings corresponding to the headline, URL, and time stamp to be written to the
	#				CSV file
	# Return:		None	
	def pushRawHeadline(self, headlineText, URL, timeDay):

		self.__outFile.write(headlineText + ", ")
		self.__outFile.write(URL + ", ")
		self.__outFile.write(timeDay + "\n")	

	# Name:			crawlUSGovAnnouncements
	# Description:	WebScraper class method which scrapes https://www.us-cert.gov/announcements
	# Parameters:	None
	# Return:		None	
	def crawlUSGovAnnouncements(self):

		siteRequest = Request(self.__USGovAnnouncementsURL, headers={'User-Agent': 'Mozilla/5.0'})
		client = urlopen(siteRequest)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "field-content"})

		for item in items:
			if not item.a == None: 
				parsedText = self.parseText(item.a.text)
				urlString = item.a.get('href')
				timeDayString = self.getTimeDate()
				self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlUSGovAlerts
	# Description:	WebScraper class method which scrapes https://www.us-cert.gov/ncas/alerts
	# Parameters:	None
	# Return:		None			
	def crawlUSGovAlerts(self):

		siteRequest = Request(self.__USGovAlertsURL, headers={'User-Agent': 'Mozilla/5.0'})
		client = urlopen(siteRequest)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("span", {"class": "document_title"})

		for item in items:
			if not item.a == None: 
				parsedText = self.parseText(item.a.text)
				urlString = item.a.get('href')
				if urlString[0] == '/':
					urlString = self.__USGovAnnouncementsURL[:-12] + urlString
				timeDayString = self.getTimeDate()
				self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlUKGovAlerts
	# Description:	WebScraper class method which scrapes https://www.ncsc.gov.uk/index/alerts-and-advisories
	# Parameters:	None
	# Return:		None			
	def crawlUKGovAlerts(self):

		client = self.makeURLConnection(self.__UKGovAlertsURL)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "result-item-wrapper"})

		for item in items:
			parsedText = self.parseText(item.h4.a.text)
			urlString = item.h4.a.get('href')
			if urlString[0] == '/':
				urlString = self.__securityWeekURL[:-28] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlCanadaAlerts
	# Description:	WebScraper class method which scrapes https://www.publicsafety.gc.ca/cnt/rsrcs/cybr-ctr/index-en.aspx#al
	# Parameters:	None
	# Return:		None		
	def crawlCanadaAlerts(self):

		client = self.makeURLConnection(self.__CanadaAlertsURL)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("li", {"class": ""})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			if urlString[0] == '/':
				urlString = self.__securityWeekURL[:-36] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)			

	# Name:			crawlReuters
	# Description:	WebScraper class method which scrapes https://www.reuters.com/news/archive/cybersecurity
	# Parameters:	None
	# Return:		None		
	def crawlReuters(self):

		client = self.makeURLConnection(self.__reutersURL)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "story-content"})

		for item in items:
			parsedText = self.parseText(item.a.h3.text)
			parsedText = self.removeWhitespace(parsedText)
			urlString = item.a.get('href')
			if urlString[0] == '/':
				urlString = self.__securityWeekURL[:-27] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)		
	
	# Name:			crawlSecurityAffairs
	# Description:	WebScraper class method which scrapes http://securityaffairs.co/wordpress/
	# Parameters:	None
	# Return:		None		
	def crawlSecurityAffairs(self):

		client = self.makeURLConnection(self.__securityAffairsURL)
		page = client.read()
		client.close()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "post_header single_post"})

		for item in items:
			parsedText = self.parseText(item.h3.a.text)
			urlString = item.h3.a.get('href')	
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlHackerNews
	# Description:	WebScraper class method which scrapes https://thehackernews.com
	# Parameters:	None
	# Return:		None		
	def crawlHackerNews(self):

		client = self.makeURLConnection(self.__hackerNewsURL)
		page = client.read()
		client.close()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("a", {"class": "url entry-title page-link"})

		for item in items:
			parsedText = self.parseText(item.text)
			urlString = item.get('href')
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlThreatNews
	# Description:	WebScraper class method which scrapes https://threatpost.com/blog/
	# Parameters:	None
	# Return:		None		
	def crawlThreatNews(self):

		siteRequest = Request(self.__threatNewsURL, headers={'User-Agent': 'Mozilla/5.0'})
		client = urlopen(siteRequest)
		page = client.read()
		client.close()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("h3", {"class": "entry-title"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlComputerWorldSecurity
	# Description:	WebScraper class method which scrapes https://www.computerworld.com/category/security/
	# Parameters:	None
	# Return:		None		
	def crawlComputerWorldSecurity(self):

		client = self.makeURLConnection(self.__computerWorldURL)
		page = client.read()
		client.close()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "post-cont"})

		for item in items:
			parsedText = self.parseText(item.h3.a.text)
			urlString = item.h3.a.get('href')
			if urlString[0] == '/':
				urlString = self.__computerWorldURL[:-19] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlTechNewsSecurity
	# Description:	WebScraper class method which scrapes https://www.technewsworld.com/perl/section/tech-security
	# Parameters:	None
	# Return:		None		
	def crawlTechNewsSecurity(self):

		client = self.makeURLConnection(self.__techNewsWorldURL)
		page = client.read()
		client.close()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("td", {"class": "shadow"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			if urlString[0] == '/':
				urlString = self.__techNewsWorldURL[:-27] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlDarkReading
	# Description:	WebScraper class method which scrapes https://www.darkreading.com/attacks-breaches.asp
	# Parameters:	None
	# Return:		None		
	def crawlDarkReading(self):

		siteRequest = Request(self.__darkReadingURL, headers={'User-Agent': 'Mozilla/5.0'})
		client = urlopen(siteRequest)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("header", {"class": "strong medium"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			if urlString[0] == '/':
				urlString = self.__darkReadingURL[:-21] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlHackerCombat
	# Description:	WebScraper class method which scrapes https://hackercombat.com/
	# Parameters:	None
	# Return:		None		
	def crawlHackerCombat(self):

		siteRequest = Request(self.__hackerCombatURL, headers={'User-Agent': 'Mozilla/5.0'})
		client = urlopen(siteRequest)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "clsh2"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlSCMagazine
	# Description:	WebScraper class method which scrapes https://www.scmagazine.com/news/section/6343/
	# Parameters:	None
	# Return:		None		
	def crawlSCMagazine(self):

		client = self.makeURLConnection(self.__SCMagazineURL)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("div", {"class": "sectionHeadline"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			parsedText = self.removeWhitespace(parsedText)
			urlString = item.a.get('href')
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlSecurityMagazine
	# Description:	WebScraper class method which scrapes https://www.securitymagazine.com/topics/2236-cyber-security-news
	# Parameters:	None
	# Return:		None		
	def crawlSecurityMagazine(self):

		client = self.makeURLConnection(self.__securityMagazineURL)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("h2", {"class": "headline article-summary__headline"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)			

	# Name:			crawlSecurityWeek
	# Description:	WebScraper class method which scrapes https://www.securityweek.com/cybercrime
	# Parameters:	None
	# Return:		None		
	def crawlSecurityWeek(self):

		siteRequest = Request(self.__securityWeekURL, headers={'User-Agent': 'Mozilla/5.0'})
		client = urlopen(siteRequest)
		page = client.read()

		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("span", {"class": "field-content"})

		for item in items:
			if not item.a == None: 
				parsedText = self.parseText(item.a.text)
				urlString = item.a.get('href')
				if urlString[0] == '/':
					urlString = self.__securityWeekURL[:-11] + urlString
				timeDayString = self.getTimeDate()
				self.pushRawHeadline(parsedText, urlString, timeDayString)

	# Name:			crawlReddit
	# Description:	WebScraper class method which scrapes http://www.reddit.com/r/cybersecurity
	# Parameters:	None
	# Return:		None			
	def crawlReddit(self):

		client = self.makeURLConnection(self.__redditURL)
		page = client.read()
		client.close()
		
		soup = BeautifulSoup(page, "html.parser")
		items = soup.findAll("p", {"class": "title"})

		for item in items:
			parsedText = self.parseText(item.a.text)
			urlString = item.a.get('href')
			if urlString[0] == '/':
				urlString = self.__redditURL[:-16] + urlString
			timeDayString = self.getTimeDate()
			self.pushRawHeadline(parsedText, urlString, timeDayString)				

	# Name:			run			
	# Description:	WebScraper class method which acts as the primary interface to the class which calls all
	#				class methods to scrape 16 different cyber security resource sites and writes the scraped
	#				headlines, URLs, and a time stamp for each one, to a CSV file 
	# Parameters:	None
	# Return:		None		
	def run(self):

		print(".", end="")

		self.crawlUSGovAnnouncements()
		self.crawlUSGovAlerts()
		self.crawlUKGovAlerts()
		self.crawlCanadaAlerts()
		self.crawlReuters()
		self.crawlSecurityAffairs()
		self.crawlHackerNews()
		self.crawlThreatNews()
		self.crawlComputerWorldSecurity()
		self.crawlTechNewsSecurity()
		self.crawlDarkReading()
		self.crawlHackerCombat()
		self.crawlSCMagazine()
		self.crawlSecurityMagazine()
		self.crawlSecurityWeek()
		self.crawlReddit()

		print(".", end="")

		self.__outFile.close()
	    
