//
// Created by ROTEM on 18/01/2017.
//

#include <iostream>
#include <boost/thread/win32/thread_data.hpp>
#include "../include/ListenToKeyboard.h"
#include "../packet/Packet.h"
#include "../packet/ERRORPacket.h"
#include "../include/ListenToServer.h"
#include "../include/connectionHandler.h"

ListenToKeyboard::ListenToKeyboard(int number, ConnectionHandler* handler){
    this->connectionHandler = connectionHandler;
    _id=number;
}


void ListenToKeyboard::run() {
    Packet* packetToSend = createNewPacketFromKeyboard();
    bool success = connectionHandler->send(packetToSend);
    if (!success){
        //TODO:send error
    }
}

Packet * ListenToKeyboard::createNewPacketFromKeyboard() const {
    const short bufsize = 518;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::__cxx11::string line(buf);
    std::__cxx11::string comand(line.substr(0, line.find(" ", 0)));
    std::__cxx11::string name(line.substr(line.find(" ", 0)));
    int len=line.length();

    Packet *packetToSend = nullptr;

    if(comand.compare("LOGRQ") == 0){
        packetToSend = new LOGRQPacket(name);
        ListenToServer::status = Status::LOGRQ;
    }
    else if(comand.compare("DELRQ") == 0){
        packetToSend = new DELRQPacket(name);
        ListenToServer::status = Status::DELRQ;
    }
    else if(comand.compare("WRQ") == 0){
        packetToSend = new WRQPacket(name);
        ListenToServer::status = Status::WRQ;
    }
    else if(comand.compare("RRQ") == 0){
        packetToSend = new RRQPacket(name);
        ListenToServer::status = Status::RRQ;
    }
    else if(comand.compare("DIRQ") == 0){
        packetToSend = new DIRQPacket();
        ListenToServer::status = Status::DIRQ;
    }
    else if(comand.compare("DISC") == 0){
        packetToSend = new DISCPacket();
        ListenToServer::status = Status::DISC;
    }
    return packetToSend;
}


void ListenToKeyboard::operator()(){
    run();
    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}

