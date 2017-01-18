//
// Created by ROTEM on 18/01/2017.
//

#include "ListenToServer.h"
#include "../packet/Packet.h"

Status ListenToServer::status(Status::Normal);


void ListenToServer::run(Packet*) {


}

/*

void sendError(ERRORPacket::Errors *errorCode, const std::string &extraMsg)
{
    ERRORPacket tempVar(static_cast<short>(errorCode->ordinal()), errorCode->getErrorMsg() + extraMsg);
    conec send(connectionId, &tempVar);
}

*/
