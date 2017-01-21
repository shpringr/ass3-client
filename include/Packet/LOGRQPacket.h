#pragma once
#include "Packet.h"
#include <vector>
#include <string>

using namespace std;

class LOGRQPacket : public Packet {
private:
    LOGRQPacket(const LOGRQPacket &logRQPacket);
    LOGRQPacket& operator=(const LOGRQPacket &b);

    std::string userName;


public:
    LOGRQPacket(const std::string &userName);

    virtual string getUserName();


    virtual char* toByteArr() override ;

    virtual ~LOGRQPacket();
};


