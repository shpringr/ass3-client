#include "DISCPacket.h"

namespace packet {

    DISCPacket::DISCPacket() {
        Packet::opCode = 10;
    }

    std::vector<char> DISCPacket::toByteArr() {
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2);
//        lengthBuffer->put(shortToBytes(opCode));
//        return lengthBuffer->array_Renamed();
    }
}
