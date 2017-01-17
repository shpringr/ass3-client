#pragma once

#include "Packet.h"
#include <string>
#include <vector>

namespace packet {


    class RRQPacket : public Packet {
    private:
        std::wstring fileName;

    public:
        RRQPacket(const std::wstring &filename);

        virtual std::wstring getFileName();


        virtual std::vector<char> toByteArr() override;
    };

}
