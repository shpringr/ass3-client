#pragma once

#include "Packet.h"
#include <vector>
    class ACKPacket : public Packet {

    public:
        ACKPacket(const ACKPacket &ackPacket);
        ACKPacket& operator=(const ACKPacket &b);

        short block = 0;

        ACKPacket(short block);

        short getBlock();

        virtual char* toByteArr()  override ;

        const char *getBlockInBytes();

        virtual ~ACKPacket();
    };

