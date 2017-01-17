#pragma once

#include "Packet.h"
#include <vector>

namespace packet {


    class DISCPacket : public Packet {

    public:
        DISCPacket();


        virtual std::vector<char> toByteArr() override;
    };

}
