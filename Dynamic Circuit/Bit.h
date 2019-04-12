
//state:
//_ _ _ _   _ _ _ _ 
//7 6 5 4   3 2 1 0
//b0 is the bit value
//b1 - b6 are the neighbors
//b7 unassigned

//borders:
//_ _ _ _   _ _ _ _ 
//7 6 5 4   3 2 1 0
//b0 unassigned
//b1 - b6 are the neighbors
//b7 unassigned

class Bit
{   
    const char bitMask = 0x01;
    const char neighborMask = 0x7E;
    const char borderMask = 0x81;

    public:

        Bit();
        ~Bit();

        void setBitValue(char bitValue);
        void setNeighborConnections(char neighborConnections);
        void setBorders(char bitBorders);
        void setState(char state); 

        char getBitValue();
        bool getBit();
        char getNeighborConnections();
        char getBorders();
        char getState();

        void diagnosticPrint(bool verbose);

    private:

        char state;
        char borders;
};