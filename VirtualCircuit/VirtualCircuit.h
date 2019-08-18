
#ifndef VIRTUALCIRCUIT_H
#define VIRTUALCIRCUIT_H

#include <string>

using namespace std;

class VirtualCircuit
{   
    public:

        struct Bit
        {
            char bit;
            char connections;
        };

        VirtualCircuit();
        VirtualCircuit(int rowCount, int columnCount);
        ~VirtualCircuit();

        void run();
        void buildBoard(string fileName);
        void getOuput(string fileName);

        void diagnosticPrint();

    private:

        int rows;
        int columns;
        Bit** board;   

        void allocateBoard();
};

#endif