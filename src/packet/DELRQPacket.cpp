#include "../../include/Packet/DELRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DELRQPacket::DELRQPacket(const string &filename):fileName(filename) {
        Packet::opCode = 8;
    }

DELRQPacket::DELRQPacket(const DELRQPacket &delRQPacket)
        : fileName(delRQPacket.fileName){

    Packet::opCode = 3;
}

DELRQPacket& DELRQPacket::operator=(const DELRQPacket &b) {
    fileName = b.fileName;
    return *this;
}

    string DELRQPacket::getFilename() {
        return fileName;
    }

    char* DELRQPacket::toByteArr()  {
        char opCodeBytes[2];
        returnBytes = new char[2 + fileName.length() + 1];

        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 2 + fileName.length(); i++)
            returnBytes[i] = fileName.c_str()[i - 2];

        returnBytes[2 + fileName.length()] = '\0';

        return returnBytes;
    }

DELRQPacket::~DELRQPacket() {
    delete(returnBytes);
}

