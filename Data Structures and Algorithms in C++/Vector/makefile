CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PA02 : PA02.o SimpleVector.o
	$(CC) $(LFLAGS) PA02.o SimpleVector.o -o PA02

PA02.o : PA02.cpp
	$(CC) $(CFLAGS) PA02.cpp

SimpleVector.o : SimpleVector.cpp SimpleVector.h
	$(CC) $(CFLAGS) SimpleVector.cpp

clean:
	\rm *.o PA02

