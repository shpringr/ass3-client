#pragma once

#include "Packet.h"
#include <vector>
    class ACKPacket : public Packet {
    public:
        short block = 0;

        ACKPacket(short block);

        short getBlock();

        virtual void toByteArr(char* outChar) override ;
    };

