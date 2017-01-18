//
// Created by ROTEM on 18/01/2017.
//

#include <boost/thread/win32/thread_data.hpp>
#include "../include/ListenToServer.h"
#include "../packet/Packet.h"

Status ListenToServer::status(Status::Normal);

bool conected = true;

ListenToServer::ListenToServer(int number, ConnectionHandler* handler) {
    this->connectionHandler = handler;
    _id=number;
}


 void ListenToServer::run() {
    while (conected) {
        Packet *answerPacket = nullptr;

        if (connectionHandler->getPacket(answerPacket)) {
            process(answerPacket);
        } else {
            conected = false;
            // releaseBuffer(buf);
            //close();
            //return nullptr;
        }
    }
}

void ListenToServer::process(Packet* packet) {

}
void ListenToServer::operator()(){
    run();
    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}

/*

void sendError(ERRORPacket::Errors *errorCode, const std::string &extraMsg)
{
    ERRORPacket tempVar(static_cast<short>(errorCode->ordinal()), errorCode->getErrorMsg() + extraMsg);
    conec send(connectionId, &tempVar);
}

*/
