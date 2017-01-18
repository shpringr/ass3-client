#include "DIRQPacket.h"

    DIRQPacket::DIRQPacket() {
        Packet::opCode = 6;
    }

    char * DIRQPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        char *returnBytes = new char[2 + 1];
        shortToBytes(opCode, opCodeBytes);

        returnBytes[2] = '\0';
        return returnBytes;
    }
