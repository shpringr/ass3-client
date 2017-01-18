#pragma execution_character_set("utf-8")

#ifndef LISTEN_TO_KEYBOARD_H
#define LISTEN_TO_KEYBOARD_H

#include <stdlib.h>
#include <iostream>
#include "connectionHandler.h"
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
#include "ListenToServer.h"



class ListenToKeyboard {

private:

    shared_ptr<ConnectionHandler> connectionHandler;
    int _id;

public:
    ListenToKeyboard(int number, shared_ptr<ConnectionHandler> handler);
    void run();
    void operator()();

    Packet * createNewPacketFromKeyboard() const;
};


#endif //CLIENT_TFTPPROTOCOLCLIENT_H
