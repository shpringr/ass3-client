#include "../../include/Packet/LOGRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

LOGRQPacket::LOGRQPacket(const std::string &userName):userName(userName){
    opCode=7;
}

std::string LOGRQPacket::getUserName() {
    return userName;
}

char * LOGRQPacket::toByteArr()  {

    char *opCodeBytes = new char[2];
    const char *userNameChar = userName.c_str();
    char *returnBytes = new char[2 + userName.length() + 1];

    MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    for (unsigned int i = 2; i < 2 + userName.length(); i++)
        returnBytes[i] = userNameChar[i - 2];

    returnBytes[2 + userName.length()] = '\0';

    return returnBytes;
}

