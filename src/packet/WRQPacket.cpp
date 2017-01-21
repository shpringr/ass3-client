#include "../../include/Packet/WRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

WRQPacket::WRQPacket(const string &filename) :fileName(filename){
        Packet::opCode = 2;
    }


WRQPacket::WRQPacket(const WRQPacket &wrqPacket)
        : fileName(wrqPacket.fileName){

    Packet::opCode = 3;
}

WRQPacket& WRQPacket::operator=(const WRQPacket &b) {
    fileName = b.fileName;
    return *this;
}
    string WRQPacket::getFileName() {
        return fileName;
    }

    char * WRQPacket::toByteArr()  {
        char opCodeBytes[2];
        returnBytes = new char[2 + fileName.length() + 1];

        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < fileName.length() + 2; i++)
            returnBytes[i] = fileName.c_str()[i - 2];

        returnBytes[2 + fileName.length()] = '\0';

        return returnBytes;
    }

WRQPacket::~WRQPacket() {
    delete(returnBytes);
}

