all: project11

project11: project11.cpp list1.o
	g++ project11.cpp list1.o -o project11

list1.o: list1.cpp
	g++ -c list1.cpp

clean:
	rm -f *.o project11
