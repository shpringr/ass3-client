#pragma execution_character_set("utf-8")
#pragma once

#include <vector>

class Packet {
protected:
    short opCode = 0;

public:
        short getOpCode();

        short bytesToShort(char bytesArr[]);

        void shortToBytes(short num, char bytesArr[]);

        const char* getOpCodeInBytes();

        virtual char* toByteArr() = 0;
};