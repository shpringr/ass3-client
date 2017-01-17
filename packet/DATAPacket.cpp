#include "DATAPacket.h"

namespace packet {

    DATAPacket::DATAPacket(short packetSize, short block, std::vector<char> &data) {
        this->packetSize = packetSize;
        this->block = block;
        this->data = data;
        Packet::opCode = 3;
    }

    short DATAPacket::getPacketSize() {
        return packetSize;
    }

    short DATAPacket::getBlock() {
        return block;
    }

    std::vector<char> DATAPacket::getData() {
        return data;
    }

    std::vector<char> DATAPacket::toByteArr() {
//						ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + 2 + 2 + data.size());
//						lengthBuffer->put(shortToBytes(opCode));
//						lengthBuffer->put(shortToBytes(packetSize));
//						lengthBuffer->put(shortToBytes(block));
//						lengthBuffer->put(data);
//						return lengthBuffer->array_Renamed();
    }
}