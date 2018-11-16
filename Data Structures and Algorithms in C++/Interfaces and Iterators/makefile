CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PA04 : PA04.o InterfaceClass.o LinkedList.o StudentType.o
	$(CC) $(LFLAGS) PA04.o InterfaceClass.o LinkedList.o StudentType.o -o PA04

PA04.o : PA04.cpp InterfaceClass.cpp LinkedList.cpp StudentType.cpp
	$(CC) $(CFLAGS) PA04.cpp

InterfaceClass.o : InterfaceClass.cpp InterfaceClass.h LinkedList.cpp LinkedList.h
	$(CC) $(CFLAGS) InterfaceClass.cpp

LinkedList.o : LinkedList.cpp LinkedList.h
	$(CC) $(CFLAGS) LinkedList.cpp

StudentType.o : StudentType.cpp StudentType.h
	$(CC) $(CFLAGS) StudentType.cpp

clean:
	\rm *.o PA04

