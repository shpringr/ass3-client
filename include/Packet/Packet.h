#pragma once

#include <vector>

class Packet {
protected:
    short opCode = 0;

public:
    short getOpCode();

    const char* getOpCodeInBytes();

    virtual char* toByteArr() = 0;
    virtual ~Packet();
};