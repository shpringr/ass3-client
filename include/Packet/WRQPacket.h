#pragma once

#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class WRQPacket : public Packet {
    private:
        WRQPacket(const WRQPacket &wrqPacket);
        WRQPacket& operator=(const WRQPacket &b);

        string fileName;

    public:
        WRQPacket(const string &filename);

        virtual string getFileName();

        virtual char* toByteArr() override ;

        virtual ~WRQPacket();
    };




