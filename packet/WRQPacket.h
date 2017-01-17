#pragma once

#include "Packet.h"
#include <string>
#include <vector>

namespace packet {


    class WRQPacket : public Packet {
    private:
        std::wstring fileName;

    public:
        WRQPacket(const std::wstring &filename);

        virtual std::wstring getFileName();

        virtual std::vector<char> toByteArr() override;

    };


}
