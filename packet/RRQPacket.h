#pragma once

#include "Packet.h"
#include <string>
#include <vector>


    class RRQPacket : public Packet {
    private:
        std::wstring fileName;

    public:
        RRQPacket(const std::wstring &filename);

        virtual std::wstring getFileName();


        virtual char* toByteArr() override ;
    };


