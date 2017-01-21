#pragma once

#include "Packet.h"
#include <vector>

    class DIRQPacket : public Packet {

    public:
        DIRQPacket();


        DIRQPacket(const DIRQPacket &dirqPacket);
        DIRQPacket& operator=(const DIRQPacket &b);

        virtual char* toByteArr() override ;

        virtual ~DIRQPacket();
    };


