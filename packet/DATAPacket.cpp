#include "DATAPacket.h"

    DATAPacket::DATAPacket(short packetSize, short block, char* data) {
        this->packetSize = packetSize;
        this->block = block;
        getData(data);
        Packet::opCode = 3;
    }

void DATAPacket::getData(const char *data) {
    DATAPacket::data =new char[packetSize];
    for (unsigned int i = 0; i < packetSize; ++i) {
        DATAPacket::data[i] = data[i];
    }
}

short DATAPacket::getPacketSize() {
        return packetSize;
    }

    short DATAPacket::getBlock() {
        return block;
    }

    char* DATAPacket::getData() {
        return data;
    }

    void DATAPacket::toByteArr(char* outChar) {

        char *opCodeBytes = new char[2];
        char *sizeChar = new char[2];
        char blockChar[11];
        char * returnBytes = new char[2 + 2+ 2+ sizeof(data) + 1];

        shortToBytes(opCode, opCodeBytes);
        shortToBytes(packetSize, sizeChar);
        shortToBytes(block, blockChar);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 4; i++)
            returnBytes[i] = sizeChar[i - 2];

        for (unsigned int i = 4; i < 6; i++)
            returnBytes[i] = blockChar[i - 4];

        for (unsigned int i = 6; i < sizeof(returnBytes) - 1; i++)
            returnBytes[i] = data[i - 6];

        returnBytes[sizeof(returnBytes) - 1] = '0';

        for(int i=0; i < sizeof(returnBytes); ++i){
            outChar[i] = returnBytes[i];
        }

    }
