#include "DIRQPacket.h"

    DIRQPacket::DIRQPacket() {
        Packet::opCode = 6;
    }

    char * DIRQPacket::toByteArr()  {
        char *opCodeBytes = new char[2];

        shortToBytes(opCode, opCodeBytes);

        return opCodeBytes;
    }
