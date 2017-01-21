#include "../../include/Packet/RRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

RRQPacket::RRQPacket(const string &filename):fileName(filename) {
        opCode=1;
    }

RRQPacket::RRQPacket(const RRQPacket &rrqPacket)
        : fileName(rrqPacket.fileName){

    Packet::opCode = 3;
}

RRQPacket& RRQPacket::operator=(const RRQPacket &b) {
    fileName = b.fileName;
    return *this;
}

    string RRQPacket::getFileName() {
        return fileName;
    }

    char * RRQPacket::toByteArr()  {
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

RRQPacket::~RRQPacket() {
    delete(returnBytes);

}

