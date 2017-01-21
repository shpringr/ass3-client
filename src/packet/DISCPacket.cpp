#include "../../include/Packet/DISCPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DISCPacket::DISCPacket() {
        Packet::opCode = 10;
    }

    char* DISCPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        char *returnBytes = new char[2 + 1];
        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        returnBytes[2] = '\0';
        return returnBytes;

    }

DISCPacket::~DISCPacket() {

}
