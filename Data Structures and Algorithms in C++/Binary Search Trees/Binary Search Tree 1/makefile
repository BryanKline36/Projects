CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

PA06 : PA06.o BSTClass.o StudentType.o SimpleTimer.o
	$(CC) $(LFLAGS) PA06.o BSTClass.o StudentType.o SimpleTimer.o -o PA06

PA06.o : PA06.cpp BSTClass.h BSTClass.cpp StudentType.h StudentType.cpp SimpleTimer.h SimpleTimer.cpp
	$(CC) $(CFLAGS) PA06.cpp

BSTClass.o : BSTClass.h BSTClass.cpp
	$(CC) $(CFLAGS) BSTClass.cpp

SimpleTimer.o : SimpleTimer.h SimpleTimer.cpp
	$(CC) $(CFLAGS) SimpleTimer.cpp

StudentType.o : StudentType.h StudentType.cpp
	$(CC) $(CFLAGS) StudentType.cpp

clean:
	\rm *.o PA06

