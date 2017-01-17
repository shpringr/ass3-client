#include "DISCPacket.h"
    DISCPacket::DISCPacket() {
        Packet::opCode = 10;
    }

    char* DISCPacket::toByteArr() {
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2);
//        lengthBuffer->put(shortToBytes(opCode));
//        return lengthBuffer->array_Renamed();
    }
