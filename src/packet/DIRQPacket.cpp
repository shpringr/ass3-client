#include "../../include/Packet/DIRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DIRQPacket::DIRQPacket() {
        Packet::opCode = 6;
    }

    char * DIRQPacket::toByteArr()  {
        char *opCodeBytes = new char[2];
        char *returnBytes = new char[2 + 1];
        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

        returnBytes[2] = '\0';
        return returnBytes;
    }
