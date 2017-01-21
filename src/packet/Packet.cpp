#include "../../include/Packet/Packet.h"
#include "../../include/MessageEncoderDecoder.h"

short Packet::getOpCode() {
        return opCode;
    }

const char* Packet::getOpCodeInBytes() {
    char *opCodeArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getOpCode(),opCodeArr);
    return opCodeArr;
}

Packet::~Packet() {
}

