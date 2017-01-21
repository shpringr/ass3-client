#include "../../include/Packet/DATAPacket.h"
#include "../../include/MessageEncoderDecoder.h"

DATAPacket::DATAPacket(short packetSize, short block, char *pData)
:   packetSize(packetSize),block(block),data(pData),sizeArr(),blockArr()
{
    Packet::opCode = 3;
}

DATAPacket::DATAPacket(const DATAPacket &dataPacket)
        : packetSize(dataPacket.packetSize), block(dataPacket.block), data(dataPacket.data),sizeArr(),blockArr(){

    Packet::opCode = 3;
}

DATAPacket& DATAPacket::operator=(const DATAPacket &b) {
    packetSize = b.packetSize;
    block = b.block;
    data = b.data;
    blockArr = b.blockArr;
    sizeArr = b.sizeArr;
    return *this;
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
    sizeArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getPacketSize(),sizeArr);
    return sizeArr;
}

const char* DATAPacket::getBlockInBytes() {
    blockArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getBlock(),blockArr);
    return blockArr;
}

char *DATAPacket::toByteArr() {
    char opCodeBytes[2];
    char sizeChar[2];
    char blockChar[2];
    unsigned int size = (unsigned int) (2 + 2 + 2 + packetSize + 1);
    returnBytes= new char[size];

    MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);
    MessageEncoderDecoder::shortToBytes(packetSize, sizeChar);
    MessageEncoderDecoder::shortToBytes(block, blockChar);


    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    for (unsigned int i = 2; i < 4; i++)
        returnBytes[i] = sizeChar[i - 2];

    for (unsigned int i = 4; i < 6; i++)
        returnBytes[i] = blockChar[i - 4];

    for (unsigned int i = 6; i < size - 1; i++)
        returnBytes[i] = data[i - 6];

    returnBytes[2 + 2 + 2 + packetSize] = '\0';

    return returnBytes;
}

DATAPacket::~DATAPacket() {
    delete (data);
    delete(returnBytes);
    delete(sizeArr);
    delete(blockArr);
}
