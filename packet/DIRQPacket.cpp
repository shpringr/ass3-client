#include "DIRQPacket.h"

    DIRQPacket::DIRQPacket() {
        Packet::opCode = 6;
    }

    void DIRQPacket::toByteArr(char* outChar) {
        char *opCodeBytes = new char[2];

        shortToBytes(opCode, opCodeBytes);


        for(int i=0; i < sizeof(opCodeBytes); ++i){
            outChar[i] = opCodeBytes[i];
        }
    }
