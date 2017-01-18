#include "LOGRQPacket.h"

LOGRQPacket::LOGRQPacket(const std::string &userName) {
    this->userName = userName;
    Packet::opCode = 7;
}

std::string LOGRQPacket::getUserName() {
    return userName;
}

char * LOGRQPacket::toByteArr()  {

    char *opCodeBytes = new char[2];
    const char *userNameChar = userName.c_str();
    char *returnBytes = new char[2 + userName.length() + 1];

    shortToBytes(opCode, opCodeBytes);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    for (unsigned int i = 2; i < sizeof(returnBytes) - 1; i++)
        returnBytes[i] = userNameChar[i - 2];

    returnBytes[sizeof(returnBytes) - 1] = '\0';

    return returnBytes;
}

