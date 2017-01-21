#pragma once

#include <vector>

class Packet {
protected:
    short opCode = 0;
    char* returnBytes;
    Packet();
public:
    Packet& operator=(const Packet &b);
    Packet(const Packet &rrqPacket);

    short getOpCode();

    const char* getOpCodeInBytes();


    virtual char* toByteArr() = 0;
    virtual ~Packet();
};