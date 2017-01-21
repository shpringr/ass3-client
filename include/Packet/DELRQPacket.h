#pragma once

#include "Packet.h"
#include <string>
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class DELRQPacket : public Packet {
    private:
        DELRQPacket(const DELRQPacket &delRQPacket);
        DELRQPacket& operator=(const DELRQPacket &b);

        string fileName;

    public:
        DELRQPacket(const string &filename);

        virtual string getFilename();


        virtual char* toByteArr() override ;

        virtual ~DELRQPacket();
    };


