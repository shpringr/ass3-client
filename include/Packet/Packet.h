#pragma once

#include <vector>

class Packet {
protected:
    short opCode = 0;

public:
        short getOpCode();

        void shortToBytes(short num, char bytesArr[]);

        const char* getOpCodeInBytes();

        virtual char* toByteArr() = 0;
};