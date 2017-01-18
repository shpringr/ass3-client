#include "DISCPacket.h"
    DISCPacket::DISCPacket() {
        Packet::opCode = 10;
    }

    char* DISCPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        shortToBytes(opCode, opCodeBytes);

        return opCodeBytes;
    }
