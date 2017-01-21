
#include <stdlib.h>
#include <iostream>
#include "connectionHandler.h"
#include "Packet/LOGRQPacket.h"
#include "Packet/Packet.h"
#include "Packet/RRQPacket.h"
#include "Packet/ACKPacket.h"
#include "Packet/BCASTPacket.h"
#include "Packet/WRQPacket.h"
#include "Packet/ERRORPacket.h"
#include "Packet/DATAPacket.h"
#include "Packet/DELRQPacket.h"
#include "Packet/DIRQPacket.h"
#include "Packet/DISCPacket.h"
#include "ListenToServer.h"



class ListenToKeyboard {

private:
    shared_ptr<ConnectionHandler> connectionHandler;
    bool isFIleExists(string name);
    Packet * createNewPacketFromKeyboard();

public:
    ListenToKeyboard(shared_ptr<ConnectionHandler> handler);
    virtual ~ListenToKeyboard();

    void run();
    void operator()();
};
