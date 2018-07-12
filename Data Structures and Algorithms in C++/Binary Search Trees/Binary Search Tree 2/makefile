CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

PA07 : PA07.o BSTClass.o StudentType.o SimpleTimer.o
	$(CC) $(LFLAGS) PA07.o BSTClass.o StudentType.o SimpleTimer.o -o PA07

PA07.o : PA07.cpp BSTClass.h BSTClass.cpp StudentType.h StudentType.cpp SimpleTimer.h SimpleTimer.cpp
	$(CC) $(CFLAGS) PA07.cpp

BSTClass.o : BSTClass.h BSTClass.cpp
	$(CC) $(CFLAGS) BSTClass.cpp

SimpleTimer.o : SimpleTimer.h SimpleTimer.cpp
	$(CC) $(CFLAGS) SimpleTimer.cpp

StudentType.o : StudentType.h StudentType.cpp
	$(CC) $(CFLAGS) StudentType.cpp

clean:
	\rm *.o PA07

