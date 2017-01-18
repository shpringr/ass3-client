
#include "ListenToServer.h"
#include "../packet/Packet.h"
#include <fstream>
#include <iostream>


Status ListenToServer::status(Status::Normal);
string ListenToServer::fileName("");

ofstream ListenToServer::fileToWrite;
ifstream ListenToServer::fileTosend;


bool conected = true;

void ListenToServer::run() {
    while (conected) {
        Packet* answerPacket;

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

void ListenToServer::process(Packet* packet) {
        switch ((packet->getOpCode())) {
            case 3:
                handleDataPacket(static_cast<DATAPacket *>(packet));
                break;
            case 4:
                handleAckPacket(static_cast<ACKPacket *>(packet));
                break;
            case 5:
                handleErrorPacket(static_cast<ERRORPacket *>(packet));
                break;
            case 9:
                handleBCastPacket(static_cast<BCASTPacket *>(packet));
                break;
            default:
                //sendError(ERRORPacket::Errors::ILLEGAL_TFTP_OPERATION, L"");
                break;
        }

}

void ListenToServer::handleBCastPacket(BCASTPacket *packet) {
    if(packet->getDeletedAdd()==1){
        std::cout << "BCAST add " << fileName  <<  std::endl;
    }
    else if(packet->getDeletedAdd()==0){
        std::cout << "BCAST del " << fileName  <<  std::endl;
    }
}

void ListenToServer::handleErrorPacket(ERRORPacket* packet) {
    std::cout << "Error " << packet->getErrorCode()  <<  std::endl;
}

void ListenToServer::handleAckPacket(ACKPacket *message) {
    std::cout << "ACK " << message->getBlock() <<  std::endl;
    switch (ListenToServer::status){
        case Status::LOGRQ:
            ListenToServer::status = Status::Normal;
            break;
        case Status::WRQ:
            //TODO
            if (message->getBlock()==0){
            }
            break;
        case Status::DISC:
            //TODO
            break;
        case Status::DELRQ:
            //TODO
            break;

        }
}

void ListenToServer::handleDataPacket(DATAPacket *message) {
    switch (ListenToServer::status){
        case Status::RRQ:
            ListenToServer::fileToWrite.open(fileName);
            if (ListenToServer::fileToWrite.is_open()) {
                ListenToServer::fileToWrite.write(message->getData(), message->getPacketSize());
                connectionHandler.send(new ACKPacket(message->getBlock()));
            }
            else if (message->getPacketSize()!=512){
                ListenToServer::fileToWrite.close();
                std::cout << "RRQ " << fileName << " complete" <<  std::endl;
                ListenToServer::status = Status::Normal;
            }
            break;
         //
        case Status::DIRQ:
            //TODO
            handleAckPacket(static_cast<ACKPacket *>(packet));
            break;
           }
}

void ListenToServer::readFileIntoDataQueue(File *file) throw(IOException) {
    short blockPacket = 1;
    FileInputStream *fileInputStream = new FileInputStream(file);
    std::vector<char> dataBytes(512);
    short packetSize = static_cast<short>(fileInputStream->read(dataBytes));
    while (packetSize == 512) {
        DATAPacket *dataToSend = new DATAPacket(packetSize, blockPacket, dataBytes);
        dataQueue->add(dataToSend);
        blockPacket++;
        packetSize = static_cast<short>(fileInputStream->read(dataBytes));
    }
    if (packetSize == -1) {
        std::vector<char> lastDataBytes(0);
        DATAPacket *dataToSend = new DATAPacket(static_cast<short>(0), blockPacket, lastDataBytes);
        dataQueue->add(dataToSend);
    } else {
        dataBytes = Arrays::copyOf(dataBytes, packetSize);
        DATAPacket *dataToSend = new DATAPacket(packetSize, blockPacket, dataBytes);
        dataQueue->add(dataToSend);
    }
}

bool ListenToServer::shouldTerminate() {
    return shouldTerminate_Renamed;
}

/*

void sendError(ERRORPacket::Errors *errorCode, const std::string &extraMsg)
{
    ERRORPacket tempVar(static_cast<short>(errorCode->ordinal()), errorCode->getErrorMsg() + extraMsg);
    conec send(connectionId, &tempVar);
}

*/

/*
if (ListenToServer::status == Status::WRQ) {
    try {
        FileOutputStream *fileOutputStream = new FileOutputStream(fileToWrite);
        fileOutputStream->write(message->getData());
        ACKPacket tempVar(message->getBlock());
        connections->send(connectionId, &tempVar);

        if (message->getPacketSize() != 512) {
            delete fileOutputStream;
            broadcastMessageToLogons(static_cast<char>(1), fileToWrite->getName());
            state = L"";
        }
    }
    catch (const FileNotFoundException &e) {
        sendError(FILE_NOT_FOUND, L"");
    }
    catch (const IOException &e) {
        sendError(NOT_DEFINED, e->getMessage());
    }
}*/

}
