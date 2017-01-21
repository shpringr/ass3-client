#include "../../include/Packet/DELRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DELRQPacket::DELRQPacket(const string &filename):fileName(filename) {
        Packet::opCode = 8;
    }

    string DELRQPacket::getFilename() {
        return fileName;
    }

    char* DELRQPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        const char *fileNameChar = fileName.c_str();
        char *returnBytes = new char[2 + fileName.length() + 1];

        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 2 + fileName.length(); i++)
            returnBytes[i] = fileNameChar[i - 2];

        returnBytes[2 + fileName.length()] = '\0';

        return returnBytes;
    }

DELRQPacket::~DELRQPacket() {

}

