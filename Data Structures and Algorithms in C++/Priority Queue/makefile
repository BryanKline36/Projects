CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PA03 : PA03.o UtilityVector.o SimpleVector.o PriorityQueue.o StudentType.o
	$(CC) $(LFLAGS) PA03.o UtilityVector.o SimpleVector.o PriorityQueue.o StudentType.o -o PA03

PA03.o : PA03.cpp UtilityVector.cpp PriorityQueue.cpp StudentType.cpp
	$(CC) $(CFLAGS) PA03.cpp

PriorityQueue.o : PriorityQueue.cpp PriorityQueue.h UtilityVector.cpp UtilityVector.h SimpleVector.cpp SimpleVector.h
	$(CC) $(CFLAGS) PriorityQueue.cpp

UtilityVector.o : UtilityVector.cpp UtilityVector.h SimpleVector.cpp SimpleVector.h
	$(CC) $(CFLAGS) UtilityVector.cpp

SimpleVector.o : SimpleVector.cpp SimpleVector.h
	$(CC) $(CFLAGS) SimpleVector.cpp

StudentType.o : StudentType.cpp StudentType.h
	$(CC) $(CFLAGS) StudentType.cpp

clean:
	\rm *.o PA03

