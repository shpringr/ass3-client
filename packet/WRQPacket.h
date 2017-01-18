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

        virtual void toByteArr(char *outChar) override ;

    };



