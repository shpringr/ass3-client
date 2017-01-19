#pragma execution_character_set("utf-8")
#pragma once

#include "Packet.h"
#include <string>
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class DELRQPacket : public Packet {
    private:
        string fileName;

    public:
        DELRQPacket(const string &filename);

        virtual string getFilename();


        virtual char* toByteArr() override ;
    };


