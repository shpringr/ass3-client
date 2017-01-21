#include "../../include/Packet/DISCPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DISCPacket::DISCPacket() {
        Packet::opCode = 10;
    }

DISCPacket::DISCPacket(const DISCPacket &discPacket)
{
    Packet::opCode = 3;
}

DISCPacket& DISCPacket::operator=(const DISCPacket &b) {
    return *this;
}

    char* DISCPacket::toByteArr()  {
        char opCodeBytes[2];
        returnBytes = new char[2 + 1];
        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        returnBytes[2] = '\0';
        return returnBytes;

    }

DISCPacket::~DISCPacket() {

    delete(returnBytes);
}
