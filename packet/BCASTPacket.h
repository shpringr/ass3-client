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

        virtual void toByteArr(char * outChar) override ;
    };


