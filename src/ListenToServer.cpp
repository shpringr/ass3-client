
#include <boost/thread/win32/thread_data.hpp>
#include "../include/ListenToServer.h"


Status ListenToServer::status(Status::Normal);
string ListenToServer::fileName("");




bool ListenToServer::connected = true;

ListenToServer::ListenToServer(const ListenToServer& listenToServer){
}

ListenToServer::ListenToServer(int number, shared_ptr<ConnectionHandler> handler) :connectionHandler(handler),
_id(number){
//    dataQueue = queue<Packet *>();
}

void ListenToServer::run() {
    while (connected) {
        Packet *answerPacket = nullptr;

        if (connectionHandler->getPacket(answerPacket)) {
            process(answerPacket);
        } else {
            connected = false;
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
            if (message->getBlock()<512){
                std::cout << "WRQ " << fileName << " complete" <<  std::endl;
                ListenToServer::status = Status::Normal;
            }
            break;
        case Status::DISC:
            connected = false;
            break;
    }
}

void ListenToServer::handleDataPacket(DATAPacket *message) {
    switch (ListenToServer::status){
        case Status::RRQ:
            ListenToServer::fileToWrite.open(fileName);
            if (ListenToServer::fileToWrite.is_open()) {
                ListenToServer::fileToWrite.write(message->getData(), message->getPacketSize());
                connectionHandler->send(new ACKPacket(message->getBlock()));
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

            //handleAckPacket(static_cast<ACKPacket *>());
            break;
           }
}

void ListenToServer::readFileIntoDataQueue(){

    short blockPacket = 1;

    ListenToServer::fileTosend= ifstream(fileName, ios::in|ios::binary|ios::ate);

    ListenToServer::fileTosend.open(fileName);
    streampos size;

    if (ListenToServer::fileTosend.is_open()){
        size = ListenToServer::fileTosend.tellg();
        ListenToServer::fileCharArr = new char [size];
        ListenToServer::fileTosend.seekg (0, ios::beg);
        ListenToServer::fileTosend.read (ListenToServer::fileCharArr, (streamsize) size);
        ListenToServer::fileTosend.close();
    }

    int sizeInt = (int) size;
    short numberOfBlocks = (short) ((sizeInt / 512) + 1);
    short sizeOfLastBlock = (short) (sizeInt % 512);
    if (sizeOfLastBlock == 0)
        sizeOfLastBlock = 512;

    for (short i = 1; i <= numberOfBlocks; ++i) {
        short packetSize = 512;

        if (i == numberOfBlocks) {
            packetSize = sizeOfLastBlock;
        }

        char* data = ListenToServer::fileCharArr + (i-1)*512;

        ListenToServer::dataQueue.push(new DATAPacket(packetSize, i, data));
    }

    if (sizeOfLastBlock == 512) {
        DATAPacket *dataToSend = new DATAPacket(0, (short)(numberOfBlocks + 1), new char());
        ListenToServer::dataQueue.push((Packet *&&) dataToSend);
    }
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

