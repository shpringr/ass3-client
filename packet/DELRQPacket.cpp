#include "DELRQPacket.h"

    DELRQPacket::DELRQPacket(const string &filename) {
        fileName = filename;
        Packet::opCode = 8;
    }

    string DELRQPacket::getFilename() {
        return fileName;
    }

    char* DELRQPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        const char *fileNameChar = fileName.c_str();
        char *returnBytes = new char[2 + fileName.length() + 1];

        shortToBytes(opCode, opCodeBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < sizeof(returnBytes) - 1; i++)
            returnBytes[i] = fileNameChar[i - 2];

        returnBytes[sizeof(returnBytes) - 1] = '\0';

        return returnBytes;
    }

