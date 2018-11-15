CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PA01 : PA01.o QueueList.o ListNode.o
	$(CC) $(LFLAGS) PA01.o QueueList.o ListNode.o -o PA01

PA01.o : QueueList.h
	$(CC) $(CFLAGS) PA01.cpp

QueueList.o : QueueList.cpp QueueList.h
	$(CC) $(CFLAGS) QueueList.cpp

ListNode.o : ListNode.cpp ListNode.h
	$(CC) $(CFLAGS) ListNode.cpp

clean:
	\rm *.o PA01

