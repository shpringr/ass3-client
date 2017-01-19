#pragma execution_character_set("utf-8")
#pragma once

#include "Packet.h"
#include <vector>

    class DIRQPacket : public Packet {

    public:
        DIRQPacket();


        virtual char* toByteArr() override ;
    };


