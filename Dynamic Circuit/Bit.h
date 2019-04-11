
class Bit
{   
    const char bitMask = 0x01;
    const char neighborMask = 0x7E;

    public:

        Bit();
        ~Bit();

        void setBitValue(char bitValue);
        void setBitNeighborConnections(char neighborConnections)
        void setBitBorders(char bitBorders);
        void setState(char state); 

        char getBitValue();
        bool getBit();
        char getBitNeighborConnections();
        char getBitBorders();
        char getState();

    private:

        void DiagnosticPrint(bool verbose = false);

        char state;
        char borders;
};