#pragma once

#include "Packet.h"
#include <vector>
#include <string>

using namespace std;

class LOGRQPacket : public Packet {
private:
    std::string userName;


public:
    LOGRQPacket(const std::string &userName);

    virtual string getUserName();


    virtual void toByteArr(char *outChar) override ;
};


