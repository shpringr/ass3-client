//#include <boost/asio/buffer.hpp>
#include "../../include/Packet/ACKPacket.h"
#include "../../include/MessageEncoderDecoder.h"

ACKPacket::ACKPacket(short block) : block(block), blockArr(){
        Packet::opCode = 4;
    }

ACKPacket::ACKPacket(const ACKPacket &ackPacket)
        : block(ackPacket.block), blockArr(){

    Packet::opCode = 3;
}

ACKPacket& ACKPacket::operator=(const ACKPacket &b) {
    block = b.block;
    blockArr = b.blockArr;
    return *this;
}

    short ACKPacket::getBlock() {
        return block;
    }

const char* ACKPacket::getBlockInBytes() {
    blockArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getBlock(),blockArr );
    return blockArr ;
}
    char* ACKPacket::toByteArr()  {

        char opCodeBytes[2];
        char blockBytes[2];
        returnBytes = new char[2+2+1];

        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);
        MessageEncoderDecoder::shortToBytes(block, blockBytes);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 4; i++)
            returnBytes[i] = blockBytes[i-2];

        returnBytes[2 + 2] = '\0';

        return returnBytes;
    }


ACKPacket::~ACKPacket() {
    delete(returnBytes);
    delete(blockArr);
}