#pragma once

#include "Packet.h"
#include <vector>

    class DATAPacket : public Packet {
    public:

        ~DATAPacket();

        short packetSize = 0;
        short block = 0;
        char* data;

        DATAPacket(short packetSize, short block, char* pData);

        virtual short getPacketSize();

        virtual short getBlock();

        virtual char* getData();

        virtual char* toByteArr() override ;

        const char *getSizeInBytes();

        const char *getBlockInBytes();
    };


