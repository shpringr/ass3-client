#pragma execution_character_set("utf-8")
#pragma once

#include "Packet.h"
#include <vector>
    class ACKPacket : public Packet {
    public:
        short block = 0;

        ACKPacket(short block);

        short getBlock();

        virtual char* toByteArr()  override ;

        const char *getBlockInBytes();
    };

