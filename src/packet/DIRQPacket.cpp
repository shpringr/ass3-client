#include "../../include/Packet/DIRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DIRQPacket::DIRQPacket() {
        Packet::opCode = 6;
    }

DIRQPacket::DIRQPacket(const DIRQPacket &dirqPacket)
        {

    Packet::opCode = 3;
}

DIRQPacket& DIRQPacket::operator=(const DIRQPacket &b) {
    return *this;
}

    char * DIRQPacket::toByteArr()  {
        char opCodeBytes[2];
        returnBytes = new char[2 + 1];
        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        returnBytes[2] = '\0';
        return returnBytes;
    }

DIRQPacket::~DIRQPacket() {

    delete(returnBytes);
}
