#pragma once

#include "Packet.h"
#include <vector>

namespace packet {

    class ACKPacket : public Packet {
    public:
        short block = 0;

        ACKPacket(short block);

        virtual short getBlock();

        virtual std::vector<char> toByteArr() override;
    };

}
