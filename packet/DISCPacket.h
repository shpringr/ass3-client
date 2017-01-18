#pragma execution_character_set("utf-8")
#pragma once
#include "Packet.h"
#include <vector>
    class DISCPacket : public Packet {

    public:
        DISCPacket();


        virtual char* toByteArr() override ;
    };


