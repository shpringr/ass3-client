#include "../../include/Packet/WRQPacket.h"

    WRQPacket::WRQPacket(const string &filename) :fileName(filename){
        Packet::opCode = 2;
    }

    string WRQPacket::getFileName() {
        return fileName;
    }

    char * WRQPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        const char *fileNameChar = fileName.c_str();
        char *returnBytes = new char[2 + fileName.length() + 1];

        shortToBytes(opCode, opCodeBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < fileName.length() + 2; i++)
            returnBytes[i] = fileNameChar[i - 2];

        returnBytes[2 + fileName.length()] = '\0';

        return returnBytes;
    }

