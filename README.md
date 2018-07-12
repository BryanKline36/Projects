# Projects
Programming Projects in C, C++, and Python README

Name: Programming Projects in C, C++, and Python

Author: Bryan Kline

Dates:  August 2015 - July 2018

The Projects repository contains four main directories:

  1. Data Structures and Algorithms in C++
  2. Traffic Simulation for Smart Cities
  3. Cybersecurity Webscraper
  4. Aerial Drone Notification System

Project descriptions: 

1. The "Data Structures and Algorithms in C++" directory includes several subdirectories each containing code in C++
which implements, tests, and documents a different data structure and/or algorithm, including class header files, 
implementation files, main driver, and make files, as well as test scripts and Doxygen files.  Each program was 
completed as a project for DSA courses in C++.

2. The "Traffic Simulation for Smart Cities" project models a smart city as a Software Defined Network, a global, top-down view
of a network, which is host to a fully autonomous fleet of automobiles.  The user specifies an arbitrarily large map with any 
number of cars added to each intersection, each also given a destination intersection thereby defining a trajectory.  The 
user may also add delays at any intersection to simulate construction, lane closures, etc. The OSPF (Open Shortest Path First) 
protocol using Dijkstra's algorithm is used to route the cars through the map with the effects of both the the added delays 
as well traffic taken into consideration.  The simulation is then run two more times, first with an initial rerouting based on 
the delays and then with a congestion correction method whereby cars with similar trajectories "snap" together to
achieve a convoy effect to reduce traffic congestion.  The results of the different simulations are both printed to the 
terminal and written to a file in the form of a number of tables.  The program was developed for a networking course in C++. 

3. The "Cybersecurity Webscraper" project serves as an automated means of gathering alerts, news, and notifications about 
cybersecurity attacks, threats, and vulnerabilities by scraping 16 cybersecurity websites and dumping the raw data
into a CSV file.  The system then filters the raw data through both a dictionary and an exclusion dictionary which
ignores common terms and searches for The system also can update the dictionary if a particular term is seen in proximity
enough times with a dictionary term which allows for a flexible, evolving filter.  The final results are ranked and pushed 
into an SQLite database based on their ranking which the cybersecurity professional can then consult in order to learn of
on-going security threats and concerns.  The program was developed for a cybersecurity course in Python, C++, and SQLite.

4. The "SkyWarden: Aerial Drone Notification System" project is an alert and notification system for aerial drones created as 
a senior project for the Autonomous Robots Lab (http://www.autonomousrobotslab.com/) at the University of Nevada, Reno over the
2017-2018 year.  The system consists of three main subsystems: an on-board drone subsystem, a ground base unit subsystem,
and a GUI subsystem.  The on-board subsystem is composed of a voltage sensor and 14 LiDAR sensor array which are polled by
a microcontroller and transmitted wirelessly to the ground base unit.  The ground base unit subsystem is composed of a
Raspberry Pi which controls a number of LEDs, seven segment displays, buttons, switches, and a speaker, which continually
receives the data from the drone, displays it on the device, and issues visual and auditory alerts with any data falls below
user-defined thresholds.  The Raspberry Pi also runs a GUI which the user may use in order to view the data graphically and
to set the voltage and proximity thresholds.  The data is also streamed over the network through the Robot Operating System,
ROS, which researchers use to control and visualize the drone.  http://skywarden.tech/
