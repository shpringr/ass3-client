#pragma once

#include <vector>

class Packet {
protected:
    short opCode = 0;

public:
    virtual short getOpCode();

    // protected abstract void parssed(byte[] byteArr);

    virtual std::vector<char> toByteArr() = 0;


    //Encode short to 2 bytes
    virtual std::vector<char> shortToBytes(short num);


};


