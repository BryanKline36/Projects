all: project10

project10: project10.cpp queue2.o
	g++ project10.cpp queue2.o -o project10

queue2.o: queue2.cpp
	g++ -c queue2.cpp

clean:
	rm -f *.o project10
