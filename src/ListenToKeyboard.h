//
// Created by ROTEM on 18/01/2017.
//

#ifndef CLIENT_TFTPPROTOCOLCLIENT_H
#define CLIENT_TFTPPROTOCOLCLIENT_H
#include <stdlib.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include "../packet/LOGRQPacket.h"
#include "../packet/Packet.h"
#include "../packet/RRQPacket.h"
#include "../packet/ACKPacket.h"
#include "../packet/BCASTPacket.h"
#include "../packet/WRQPacket.h"
#include "../packet/ERRORPacket.h"
#include "../packet/DATAPacket.h"
#include "../packet/DELRQPacket.h"
#include "../packet/DIRQPacket.h"
#include "../packet/DISCPacket.h"


class ListenToKeyboard {

enum class Status {
    normal,
    readingFromServer,
    dir
};

private:
    Status status;
    ConnectionHandler connectionHandler;

public:
    ListenToKeyboard(const ConnectionHandler &connectionHandler);

    void run(Packet);

    void setStatus(const string &status);

    const string &getStatus() const;

    Packet * createNewPacketFromKeyboard() const;
};


#endif //CLIENT_TFTPPROTOCOLCLIENT_H
