#pragma once

#include "Packet.h"
#include <string>
#include <vector>

using namespace std;
#include <string>
#include <iostream>

    class RRQPacket : public Packet {
    private:
        string fileName;

    public:
        RRQPacket(const string &filename);

        virtual string getFileName();


        virtual char* toByteArr() override ;
    };


