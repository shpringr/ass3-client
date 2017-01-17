#pragma once

#include "Packet.h"
#include <vector>
    class DISCPacket : public Packet {

    public:
        DISCPacket();


        virtual std::vector<char> toByteArr() override;
    };


