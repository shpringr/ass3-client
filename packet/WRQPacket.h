#pragma once

#include "Packet.h"
#include <string>
#include <vector>

    class WRQPacket : public Packet {
    private:
        std::wstring fileName;

    public:
        WRQPacket(const std::wstring &filename);

        virtual std::wstring getFileName();

        virtual char* toByteArr() override ;

    };



