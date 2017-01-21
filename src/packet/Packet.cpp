#include "../../include/Packet/Packet.h"
#include "../../include/MessageEncoderDecoder.h"

short Packet::getOpCode() {
        return opCode;
    }

Packet::Packet(const Packet &rrqPacket) :opCode(rrqPacket.opCode), returnBytes(rrqPacket.returnBytes){

}
const char* Packet::getOpCodeInBytes() {
    char *opCodeArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getOpCode(),opCodeArr);
    return opCodeArr;
}

Packet::~Packet() {
    delete(returnBytes);
}

Packet::Packet() :opCode(), returnBytes(){

}

Packet &Packet::operator=(const Packet &b) {
    opCode = b.opCode;
    returnBytes = b.returnBytes;
    return *this;
}


