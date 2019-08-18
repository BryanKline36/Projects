all: VirtualCircuitBoard

VirtualCircuitBoard: main.cpp VirtualCircuit.o
	g++ main.cpp VirtualCircuit.o -o VirtualCircuitBoard

VirtualCircuit.o: VirtualCircuit.cpp
	g++ -c VirtualCircuit.cpp

clean:
	rm -f *.o VirtualCircuitBoard


