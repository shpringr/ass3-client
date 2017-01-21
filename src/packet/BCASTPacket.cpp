#include "../../include/Packet/BCASTPacket.h"
#include "../../include/MessageEncoderDecoder.h"
#include <string>

BCASTPacket::BCASTPacket(char deletedAdd, const string &fileName)
        : deletedAdd(deletedAdd), fileName(fileName){
    opCode = 9;
}

BCASTPacket::BCASTPacket(const BCASTPacket &bCASTPacket)
        : deletedAdd(bCASTPacket.deletedAdd), fileName(bCASTPacket.fileName){

    Packet::opCode = 3;
}

BCASTPacket& BCASTPacket::operator=(const BCASTPacket &b) {
    deletedAdd = b.deletedAdd;
    fileName = b.fileName;
    return *this;
}

char BCASTPacket::getDeletedAdd() {
    return deletedAdd;
}

string BCASTPacket::getFileName() {
    return fileName;
}

char* BCASTPacket::toByteArr() {

    char opCodeBytes[2];
    returnBytes = new char[2 + 1 + fileName.length() + 1];

    MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    returnBytes[2] = deletedAdd;

    for (unsigned int j = 3; j < 2 + 1 + fileName.length(); j++) {
        returnBytes[j] = fileName.c_str()[j - 3];
    }

    returnBytes[2 + 1 + fileName.length()] = '\0';

    return returnBytes;

}

BCASTPacket::~BCASTPacket() {
    delete(returnBytes);
}
