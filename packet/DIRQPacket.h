#pragma once

#include "Packet.h"
#include <vector>

namespace packet {


    class DIRQPacket : public Packet {

    public:
        DIRQPacket();


        virtual std::vector<char> toByteArr() override;
    };

}
