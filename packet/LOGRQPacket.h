#pragma once

#include "Packet.h"
#include <string>
#include <vector>


class LOGRQPacket : public Packet {
private:
    std::string userName;


public:
    LOGRQPacket(const std::string &userName);

    virtual std::string getUserName();


    virtual char* toByteArr() override ;
};


