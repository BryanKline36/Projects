CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PA08 : PA08.o SimpleVector.o ClassType.o RoomType.o SimpleTimer.o
	$(CC) $(LFLAGS) PA08.o SimpleVector.o ClassType.o RoomType.o SimpleTimer.o -o PA08

PA08.o : PA08.cpp SimpleVector.cpp ClassType.h RoomType.h SimpleTimer.h
	$(CC) $(CFLAGS) PA08.cpp

SimpleVector.o : SimpleVector.cpp SimpleVector.h
	$(CC) $(CFLAGS) SimpleVector.cpp

RoomType.o : RoomType.cpp RoomType.h
	$(CC) $(CFLAGS) RoomType.cpp

ClassType.o : ClassType.cpp ClassType.h
	$(CC) $(CFLAGS) ClassType.cpp

SimpleTimer.o : SimpleTimer.cpp SimpleTimer.h
	$(CC) $(CFLAGS) SimpleTimer.cpp

clean:
	\rm *.o PA08

