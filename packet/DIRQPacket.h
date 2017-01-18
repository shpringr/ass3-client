#pragma once

#include "Packet.h"
#include <vector>

    class DIRQPacket : public Packet {

    public:
        DIRQPacket();


        virtual void toByteArr(char *outChar) override ;
    };


