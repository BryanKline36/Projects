all: project10

project10: project10.cpp queue1.o
	g++ project10.cpp queue1.o -o project10

queue1.o: queue1.cpp
	g++ -c queue1.cpp

clean:
	rm -f *.o project10
