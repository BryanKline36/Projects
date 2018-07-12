CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PA09 : PA09.o HeapType.o SimpleVector.o ClassType.o RoomType.o SimpleTimer.o
	$(CC) $(LFLAGS) PA09.o HeapType.o SimpleVector.o ClassType.o RoomType.o SimpleTimer.o -o PA09

PA09.o : PA09.cpp HeapType.cpp SimpleVector.cpp ClassType.h RoomType.h SimpleTimer.h
	$(CC) $(CFLAGS) PA09.cpp

HeapType.o : HeapType.cpp HeapType.h
	$(CC) $(CFLAGS) HeapType.cpp

SimpleVector.o : SimpleVector.cpp SimpleVector.h
	$(CC) $(CFLAGS) SimpleVector.cpp

RoomType.o : RoomType.cpp RoomType.h
	$(CC) $(CFLAGS) RoomType.cpp

ClassType.o : ClassType.cpp ClassType.h
	$(CC) $(CFLAGS) ClassType.cpp

SimpleTimer.o : SimpleTimer.cpp SimpleTimer.h
	$(CC) $(CFLAGS) SimpleTimer.cpp

clean:
	\rm *.o PA09

