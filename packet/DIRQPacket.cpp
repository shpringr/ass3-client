#include "DIRQPacket.h"

namespace packet {

    DIRQPacket::DIRQPacket() {
        Packet::opCode = 6;
    }

    std::vector<char> DIRQPacket::toByteArr() {
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2);
//        lengthBuffer->put(shortToBytes(opCode));
//        return lengthBuffer->array_Renamed();
    }
}
