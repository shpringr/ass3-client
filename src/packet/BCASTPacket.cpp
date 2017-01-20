#include "../../include/Packet/BCASTPacket.h"
#include <string>

BCASTPacket::BCASTPacket(char deletedAdd, const string &fileName)
        : deletedAdd(deletedAdd), fileName(fileName){
    opCode = 9;
}

char BCASTPacket::getDeletedAdd() {
    return deletedAdd;
}

string BCASTPacket::getFileName() {
    return fileName;
}

char* BCASTPacket::toByteArr() {

    char *opCodeBytes = new char[2];
    const char *filenameChar = fileName.c_str();
    char *returnBytes = new char[2 + 1 + fileName.length() + 1];

    shortToBytes(opCode, opCodeBytes);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    returnBytes[2] = deletedAdd;

    for (unsigned int j = 3; j < 2 + 1 + fileName.length(); j++) {
        returnBytes[j] = filenameChar[j - 3];
    }

    returnBytes[2 + 1 + fileName.length()] = '\0';

    return returnBytes;

}
