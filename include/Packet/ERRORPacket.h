#pragma execution_character_set("utf-8")
#pragma once
#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class ERRORPacket : public Packet {

    public:
        short errorCode = 0;
        string errMsg;

    public:
        ERRORPacket(short errorCode, const string &errMsg);

        virtual short getErrorCode();

        virtual string getErrMsg();

    virtual char* toByteArr() override ;

    const char *getErrorCodeInBytes();
};



