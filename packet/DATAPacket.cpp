#include "DATAPacket.h"

DATAPacket::DATAPacket(short packetSize, short block, char *data) {
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

char *DATAPacket::getData() {
    return data;
}

char *DATAPacket::toByteArr() {

    char *opCodeBytes = new char[2];
    char *sizeChar = new char[2];
    char *blockChar = new char[2];
    char *returnBytes = new char[2 + 2 + 2 + packetSize + 1];

    shortToBytes(opCode, opCodeBytes);
    shortToBytes(packetSize, sizeChar);
    shortToBytes(block, blockChar);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    for (unsigned int i = 2; i < 4; i++)
        returnBytes[i] = sizeChar[i - 2];

    for (unsigned int i = 4; i < 6; i++)
        returnBytes[i] = blockChar[i - 4];

    for (unsigned int i = 6; i < 2 + 2 + 2 + packetSize; i++)
        returnBytes[i] = data[i - 6];

    returnBytes[2 + 2 + 2 + packetSize] = '\0';

    return returnBytes;

}
