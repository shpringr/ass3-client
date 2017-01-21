//#include <boost/asio/buffer.hpp>
#include "../../include/Packet/ACKPacket.h"
#include "../../include/MessageEncoderDecoder.h"

ACKPacket::ACKPacket(short block) : block(block){
        Packet::opCode = 4;
    }

    short ACKPacket::getBlock() {
        return block;
    }

const char* ACKPacket::getBlockInBytes() {
    char *blockArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getBlock(),blockArr );
    return blockArr ;
}
    char* ACKPacket::toByteArr()  {

        char *opCodeBytes = new char[2];
        char *blockBytes = new char[2];
        char *returnBytes = new char[2+2+1];

        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);
        MessageEncoderDecoder::shortToBytes(block, blockBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 4; i++)
            returnBytes[i] = blockBytes[i-2];

        returnBytes[2 + 2] = '\0';

        return returnBytes;
    }


ACKPacket::~ACKPacket() {}