#include <boost/asio/buffer.hpp>
#include "ACKPacket.h"
    ACKPacket::ACKPacket(short block) {
        this->block = block;
        Packet::opCode = 4;
    }

    short ACKPacket::getBlock() {
        return block;
    }

    void ACKPacket::toByteArr(char* outChar) {

        char *opCodeBytes = new char[2];
        char *blockBytes = new char[2];
        char returnBytes[2+2];

        shortToBytes(opCode, opCodeBytes);
        shortToBytes(block, blockBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 4; i++)
            returnBytes[i] = blockBytes[i-2];

        for(int i=0; i < sizeof(returnBytes); ++i){
            outChar[i] = returnBytes[i];
        }
    }
