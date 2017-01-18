#include "Packet.h"

    short Packet::getOpCode() {
        return opCode;
    }

void Packet::shortToBytes(short num, char *bytesArr) {

    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

short Packet::bytesToShort(char *bytesArr) {
        short result = (short) ((bytesArr[0] & 0xff) << 8);
        result += (short) (bytesArr[1] & 0xff);
        return result;
    }

