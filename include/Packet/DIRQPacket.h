#pragma once

#include "Packet.h"
#include <vector>

    class DIRQPacket : public Packet {

    public:
        DIRQPacket();


        virtual char* toByteArr() override ;

        virtual ~DIRQPacket();
    };


