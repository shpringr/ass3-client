//
// Created by ROTEM on 18/01/2017.
//

#include <iostream>
#include "ListenToKeyboard.h"
#include "../packet/Packet.h"
#include "../packet/ERRORPacket.h"
#include "ListenToServer.h"
#include "../include/connectionHandler.h"


//ListenToKeyboard::ListenToKeyboard(ConnectionHandler *connectionHandler) : connectionHandler(*connectionHandler) {
//}


void ListenToKeyboard::run(Packet*) {

void ListenToKeyboard::run() {
    Packet* packetToSend = createNewPacketFromKeyboard();
    bool success = connectionHandler.send(packetToSend);
    if (!success){
        ///send error
    }
}

Packet * ListenToKeyboard::createNewPacketFromKeyboard() const {
    const short bufsize = 518;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::__cxx11::string line(buf);
    std::__cxx11::string comand(line.substr(0, line.find(" ", 0)));
    std::__cxx11::string name(line.substr(line.find("<", 0), line.find(">", 0)));
    int len=line.length();

    Packet *packetToSend = nullptr;

    if(comand.compare("LOGRQ")){
        packetToSend = new LOGRQPacket(name);
        ListenToServer::status = Status::LOGRQ;
    }
    else if(comand.compare("DELRQ")){
        packetToSend = new DELRQPacket(name);
        ListenToServer::status = Status::DELRQ;
    }
    else if(comand.compare("WRQ")){
        packetToSend = new WRQPacket(name);
        ListenToServer::status = Status::WRQ;
    }
    else if(comand.compare("RRQ")){
        packetToSend = new RRQPacket(name);
        ListenToServer::status = Status::RRQ;
    }
    else if(comand.compare("DIRQ")){
        packetToSend = new DIRQPacket();
        ListenToServer::status = Status::DIRQ;
    }
    else if(comand.compare("DISC")){
        packetToSend = new DISCPacket();
        ListenToServer::status = Status::DISC;
    }
    return packetToSend;
}


