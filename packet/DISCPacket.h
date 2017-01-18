#pragma once

#include "Packet.h"
#include <vector>
    class DISCPacket : public Packet {

    public:
        DISCPacket();


        virtual void toByteArr(char *outChar) override ;
    };


