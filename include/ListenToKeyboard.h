
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
    int _id;

public:
    ListenToKeyboard(int number, shared_ptr<ConnectionHandler> handler);
    void run();
    void operator()();

    Packet * createNewPacketFromKeyboard() const;

    bool isFIleExists(string name) const;
};
