//
// Created by ROTEM on 18/01/2017.
//

#include <iostream>
#include <boost/thread/win32/thread_data.hpp>
#include "../include/ListenToKeyboard.h"
#include "../include/Packet/Packet.h"
#include "../include/Packet/ERRORPacket.h"
#include "../include/ListenToServer.h"
#include "../include/connectionHandler.h"

ListenToKeyboard::ListenToKeyboard(int number, shared_ptr<ConnectionHandler> handler){
    connectionHandler=handler;
            _id=number;
//    dataQueue = queue<Packet *>();
}

void ListenToKeyboard::run() {
    while (ListenToServer::connected) {
        Packet *packetToSend = createNewPacketFromKeyboard();
        if (packetToSend!= nullptr)
        {
            bool success = connectionHandler->send(packetToSend);
            if (!success) {
                //TODO:send error
            }
            else if (DISCPacket* answerPacket = dynamic_cast<DISCPacket*>(packetToSend))
            {
                while(ListenToServer::connected)
                {}
            }
        } else{
            cout << "Error 4";
            //TODO : DELETE
            cout << "not a valid option" << endl;

        }
    }
    cout << "disconnected keyyboard!"<<endl;
}

Packet * ListenToKeyboard::createNewPacketFromKeyboard() const {
    const short bufsize = 518;
    char buf[bufsize];
    cin.getline(buf, bufsize);
    string line(buf);
    string name;
    string comand(line.substr(0, line.find(" ", 0)));
    if (line.find(" ", 0) != string::npos)
        name= line.substr(comand.size() + 1, line.length());

    Packet *packetToSend = nullptr;

    if(comand.compare("LOGRQ") == 0){
        if (!name.empty()) {
            packetToSend = new LOGRQPacket(name);
            ListenToServer::status = Status::LOGRQ;
        }
    }
    else if(comand.compare("DELRQ") == 0){
        if (!name.empty()) {
            packetToSend = new DELRQPacket(name);
            ListenToServer::status = Status::DELRQ;
        }
    }
    else if(comand.compare("WRQ") == 0){
        if (!name.empty()) {
            if (isFIleExists(name)) {
                packetToSend = new WRQPacket(name);
                ListenToServer::status = Status::WRQ;
                ListenToServer::fileName = name;
            } else
            {
                packetToSend = new ERRORPacket(1, "");
                cout << "file not found in client " << name << endl;
            }
        }
    }
    else if(comand.compare("RRQ") == 0){
        if (!name.empty()) {
            packetToSend = new RRQPacket(name);
            ListenToServer::status = Status::RRQ;
            ListenToServer::fileName = name;
        }
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

bool ListenToKeyboard::isFIleExists(string name) const {

    string fullFileName = "./" + name;

    ifstream tryOpen;
    tryOpen.open(fullFileName);

    bool isOpened = tryOpen.is_open();
    if (isOpened)
        tryOpen.close();
    return isOpened;
}

