#include "../../include/Packet/Packet.h"

    short Packet::getOpCode() {
        return opCode;
    }

void Packet::shortToBytes(short num, char *bytesArr) {

    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

const char* Packet::getOpCodeInBytes() {
    char *opCodeArr = new char[2];
    shortToBytes(getOpCode(),opCodeArr);
    return opCodeArr;
}

