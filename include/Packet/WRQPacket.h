#pragma execution_character_set("utf-8")
#pragma once

#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class WRQPacket : public Packet {
    private:
        string fileName;

    public:
        WRQPacket(const string &filename);

        virtual string getFileName();

        virtual char* toByteArr() override ;

    };



