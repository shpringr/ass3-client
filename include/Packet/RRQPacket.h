#pragma once

#include "Packet.h"
#include <vector>

using namespace std;
#include <string>
#include <iostream>

    class RRQPacket : public Packet {
    private:
        RRQPacket(const RRQPacket &rrqPacket);
        RRQPacket& operator=(const RRQPacket &b);

        string fileName;

    public:
        RRQPacket(const string &filename);

        virtual string getFileName();

        virtual char* toByteArr() override ;

        virtual ~RRQPacket();
    };


