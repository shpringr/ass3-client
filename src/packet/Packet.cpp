#include "../../include/Packet/Packet.h"
#include "../../include/MessageEncoderDecoder.h"

short Packet::getOpCode() {
        return opCode;
    }

Packet::Packet(const Packet &rrqPacket) :opCode(rrqPacket.opCode), returnBytes(rrqPacket.returnBytes),opCodeArr(){

}
const char* Packet::getOpCodeInBytes() {
    opCodeArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getOpCode(),opCodeArr);
    return opCodeArr;
}

Packet::~Packet() {
    delete(returnBytes);
    delete(opCodeArr);
}

Packet::Packet() : opCode(), returnBytes(),opCodeArr(){
}

Packet &Packet::operator=(const Packet &b) {
    opCode = b.opCode;
    opCodeArr = b.opCodeArr;
    returnBytes = b.returnBytes;
    return *this;
}


