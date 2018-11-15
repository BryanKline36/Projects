CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

PA11 : PA11.o SimpleQueue.o SimpleStack.o PathType.o VertexType.o
	$(CC) $(LFLAGS) PA11.o SimpleQueue.o SimpleStack.o PathType.o VertexType.o -o PA11

PA11.o : PA11.cpp SimpleQueue.h SimpleQueue.cpp SimpleStack.h SimpleStack.cpp PathType.h PathType.cpp VertexType.h VertexType.cpp
	$(CC) $(CFLAGS) PA11.cpp

SimpleStack.o : SimpleStack.h SimpleStack.cpp
	$(CC) $(CFLAGS) SimpleStack.cpp

SimpleQueue.o : SimpleQueue.h SimpleQueue.cpp
	$(CC) $(CFLAGS) SimpleQueue.cpp

VertexType.o : VertexType.h VertexType.cpp
	$(CC) $(CFLAGS) VertexType.cpp

PathType.o : PathType.h PathType.cpp
	$(CC) $(CFLAGS) PathType.cpp

clean:
	\rm *.o PA11

