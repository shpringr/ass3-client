#pragma execution_character_set("utf-8")
#pragma once

#include "Packet.h"
#include <vector>

    class DATAPacket : public Packet {
    public:
        short packetSize = 0;
        short block = 0;
        char* data;

        DATAPacket(short packetSize, short block, char* data);

        virtual short getPacketSize();

        virtual short getBlock();

        virtual char* getData();

        virtual char* toByteArr() override ;

        const char *getSizeInBytes();

        const char *getBlockInBytes();
    };


