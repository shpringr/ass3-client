#pragma once

#include "Packet.h"
#include <vector>

    class DIRQPacket : public Packet {

    public:
        DIRQPacket();


        virtual std::vector<char> toByteArr() override;
    };


