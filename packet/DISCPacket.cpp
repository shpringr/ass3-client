#include "DISCPacket.h"
    DISCPacket::DISCPacket() {
        Packet::opCode = 10;
    }

    void DISCPacket::toByteArr(char* outChar) {
        char *opCodeBytes = new char[2];
        shortToBytes(opCode, opCodeBytes);

        for(int i=0; i < sizeof(opCodeBytes); ++i) {

            outChar[i] = opCodeBytes[i];
        }
    }
