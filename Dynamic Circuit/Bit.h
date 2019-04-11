
// 0000 0000
// 7654 3210
//b0 is the value of the Bit,  

class Bit
{   
    public:

        Bit();
        ~Bit();

    void setBitValue(char bitValue);
    void setBitNeighborsConnections(char neighborConnections)
    void setBitNeighbors();

    bool getBitValue();
    char getBitNeighbors();

    private:

    char bit;

};