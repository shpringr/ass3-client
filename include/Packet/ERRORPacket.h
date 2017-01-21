#pragma once
#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class ERRORPacket : public Packet {

    public:
        ERRORPacket(const ERRORPacket &errPacket);
        ERRORPacket& operator=(const ERRORPacket &b);

        short errorCode = 0;
        string errMsg;

    public:
        ERRORPacket(short errorCode, const string &errMsg);

        virtual short getErrorCode();

        virtual string getErrMsg();

    virtual char* toByteArr() override ;

    const char *getErrorCodeInBytes();

        virtual ~ERRORPacket();
    };



