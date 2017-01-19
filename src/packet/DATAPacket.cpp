#include "../../include/Packet/DATAPacket.h"

DATAPacket::DATAPacket(short packetSize, short block, char *pData) {
    this->packetSize = packetSize;
    this->block = block;
    this->data = pData;
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

const char* DATAPacket::getSizeInBytes() {
    char *sizeArr = new char[2];
    shortToBytes(getPacketSize(),sizeArr);
    return sizeArr;
}

const char* DATAPacket::getBlockInBytes() {
    char *blockArr = new char[2];
    shortToBytes(getBlock(),blockArr);
    return blockArr;
}

char *DATAPacket::toByteArr() {

    char* data2 = data;
    char opCodeBytes[2];
    char sizeChar[2];
    char blockChar[2];
    std::vector<char> returnBytes(2 + 2 + 2 + packetSize + 1);

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

    return &returnBytes[0];

}

DATAPacket::~DATAPacket() {
    delete data;

}
