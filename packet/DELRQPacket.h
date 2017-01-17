#pragma once

#include "Packet.h"
#include <string>
#include <vector>

    class DELRQPacket : public Packet {
    private:
        std::wstring fileName;

    public:
        DELRQPacket(const std::wstring &filename);

        virtual std::wstring getFilename();


        virtual std::vector<char> toByteArr() override;
    };


