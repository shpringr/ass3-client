
#include <vector>

class Packet {
protected:
    short opCode = 0;

public:
    virtual short getOpCode();

    // protected abstract void parssed(byte[] byteArr);

        virtual short bytesToShort(char *bytesArr) = 0;


        //Encode short to 2 bytes
        virtual void shortToBytes(short num, char *bytesArr) = 0;

        virtual char* toByteArr() = 0;

};


