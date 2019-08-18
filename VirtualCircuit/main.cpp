#include <iostream>
#include "VirtualCircuit.h"

using namespace std;

int main(int argc, char* argv[])
{
    VirtualCircuit virtualCircuit;

    virtualCircuit.buildBoard("input_0");
    virtualCircuit.diagnosticPrint();

    return 0;
}