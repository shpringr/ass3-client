//
// Created by ROTEM on 18/01/2017.
//

#include "ListenToServer.h"
#include "../packet/Packet.h"

Status ListenToServer::status(Status::Normal);

bool conected = true;

void ListenToServer::run() {
    while (conected) {
        Packet answerPacket;

        if (connectionHandler.getPacket(answerPacket)) {
            process(answerPacket);
        } else {
            conected = false;
            // releaseBuffer(buf);
            //close();
            //return nullptr;
        }
    }
}

void ListenToServer::process(Packet packet) {

}

/*

void sendError(ERRORPacket::Errors *errorCode, const std::string &extraMsg)
{
    ERRORPacket tempVar(static_cast<short>(errorCode->ordinal()), errorCode->getErrorMsg() + extraMsg);
    conec send(connectionId, &tempVar);
}

*/
