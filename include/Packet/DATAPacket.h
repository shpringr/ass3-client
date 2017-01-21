#pragma once

#include "Packet.h"
#include <vector>

    class DATAPacket : public Packet {
    public:
        DATAPacket(short packetSize, short block, char* pData);
        DATAPacket(const DATAPacket &dataPacket);
        DATAPacket& operator=(const DATAPacket& b);
        ~DATAPacket();

        short packetSize = 0;
        short block = 0;
        char* data;

        virtual short getPacketSize();

        virtual short getBlock();

        virtual char* getData();

        virtual char* toByteArr() override ;

        const char *getSizeInBytes();

        const char *getBlockInBytes();

    };


