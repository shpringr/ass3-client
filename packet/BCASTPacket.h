#pragma execution_character_set("utf-8")
#pragma once

#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>


    class BCASTPacket : public Packet {
    public:
        char deletedAdd = 0;
        string fileName;

        BCASTPacket(char deletedAdd, const string &fileName);

        virtual char getDeletedAdd();

        virtual string getFileName();

        virtual char* toByteArr() override ;
    };


