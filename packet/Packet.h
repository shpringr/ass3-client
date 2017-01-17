#pragma once

#include <vector>

class Packet {
protected:
    short opCode = 0;

public:
        short getOpCode();

        short bytesToShort(char bytesArr[]);

        void shortToBytes(short num, char bytesArr[]);

        virtual char* toByteArr() = 0;
};


