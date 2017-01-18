#include "RRQPacket.h"

    RRQPacket::RRQPacket(const string &filename) {
        fileName = filename;
        Packet::opCode = 1;
    }

    string RRQPacket::getFileName() {
        return fileName;
    }

    void RRQPacket::toByteArr(char* outChar) {
        char *opCodeBytes = new char[2];
        const char *fileNameChar = fileName.c_str();
        char *returnBytes = new char[2 + fileName.length() + 1];

        shortToBytes(opCode, opCodeBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < sizeof(returnBytes) - 1; i++)
            returnBytes[i] = fileNameChar[i - 2];

        returnBytes[sizeof(returnBytes) - 1] = '0';

        for(int i=0; i < sizeof(returnBytes); ++i){
            outChar[i] = returnBytes[i];
        }

    }

