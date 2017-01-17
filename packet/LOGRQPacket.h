#pragma once

#include "Packet.h"
#include <string>
#include <vector>

namespace packet {


    class LOGRQPacket : public Packet {
    private:
        std::wstring userName;


    public:
        LOGRQPacket(const std::wstring &userName);

        virtual std::wstring getUserName();


        virtual std::vector<char> toByteArr() override;
    };

}
