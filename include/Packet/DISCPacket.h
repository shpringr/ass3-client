#pragma once
#include "Packet.h"
#include <vector>
    class DISCPacket : public Packet {

    public:
        DISCPacket();


        virtual char* toByteArr() override ;

        virtual ~DISCPacket();
    };


