#pragma once

#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>


    class BCASTPacket : public Packet {
    public:
        BCASTPacket(const BCASTPacket &bCASTPacket);
        BCASTPacket& operator=(const BCASTPacket &b);

        char deletedAdd = 0;
        string fileName;

        BCASTPacket(char deletedAdd, const string &fileName);

        virtual char getDeletedAdd();

        virtual string getFileName();

        virtual char* toByteArr() override ;

        virtual ~BCASTPacket();
    };


