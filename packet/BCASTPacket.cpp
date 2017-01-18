#include "BCASTPacket.h"
#include <string>

BCASTPacket::BCASTPacket(char deletedAdd, const string &fileName) {
    this->deletedAdd = deletedAdd;
    this->fileName = fileName;
    Packet::opCode = 9;
}

char BCASTPacket::getDeletedAdd() {
    return deletedAdd;
}

string BCASTPacket::getFileName() {
    return fileName;
}

void BCASTPacket::toByteArr(char *outChar) {

    char *opCodeBytes = new char[2];
    const char *filenameChar = fileName.c_str();
    char returnBytes[2 + 1 + fileName.length() + 1];

    shortToBytes(opCode, opCodeBytes);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    returnBytes[2] = deletedAdd;

    for (unsigned int j = 3; j < sizeof(returnBytes) - 1; j++) {
        returnBytes[j] = filenameChar[j - 3];
    }
    returnBytes[sizeof(returnBytes) - 1] = '0';

    for (int i = 0; i < sizeof(returnBytes); ++i) {
        outChar[i] = returnBytes[i];
    }
}
