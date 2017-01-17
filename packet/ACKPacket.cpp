#include "ACKPacket.h"

namespace packet {

    ACKPacket::ACKPacket(short block) {
        this->block = block;
        Packet::opCode = 4;
    }

    short ACKPacket::getBlock() {
        return block;
    }

    std::vector<char> ACKPacket::toByteArr() {
//
//
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + 2);
//        lengthBuffer->put(shortToBytes(opCode));
//        lengthBuffer->put(shortToBytes(block));
//        return lengthBuffer->array_Renamed();
    }
}