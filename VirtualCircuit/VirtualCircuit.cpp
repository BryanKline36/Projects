
#ifndef VIRTUALCIRCUIT_CPP
#define VIRTUALCIRCUIT_CPP

#include <iostream>
#include <fstream>
#include "VirtualCircuit.h"


using namespace std;

VirtualCircuit::VirtualCircuit()
{
    rows = 10;
    columns = 10;

    allocateBoard();       
}

VirtualCircuit::VirtualCircuit(int rowCount, int columnCount)
{
    rows = rowCount;
    columns = columnCount;
    
    allocateBoard();       
}

VirtualCircuit::~VirtualCircuit()
{
    int index; 
    
    if(board != NULL)
    {
        for(index = 0; index < rows; ++index)
        {
            if(board[index] != NULL)
            {
                delete[] board[index];
            }
        }

        delete board;
    }
}

void VirtualCircuit::run()
{

}

void VirtualCircuit::buildBoard(string fileName)
{
    int row = 0, column = 0;
    char input;
    ifstream inFile;

    inFile.open(fileName);

    while(inFile >> input)
    {
        
        if(row < rows && column < columns)
        {
            board[row][column].bit = input;
            inFile >> input;
            inFile >> input;
            board[row][column].connections = input;
            column++;
        }

        if(column == columns)
        {
            column = 0;
            row++;
        }
    }
}

void VirtualCircuit::getOuput(string fileName)
{

}

void VirtualCircuit::diagnosticPrint()
{
    int row, column;

    for(row = 0; row < rows; ++row)
    {
        for(column = 0; column <columns; ++column)
        {
            cout << board[row][column].bit << ":" << board[row][column].connections << " ";    
        }
        cout << endl;
    }
    cout << endl;
}

void VirtualCircuit::allocateBoard()
{
    int index;

    board = new Bit*[rows];

    for(index = 0; index < rows; ++index)
    {
        board[index] = new Bit[columns];
    }
}

#endif