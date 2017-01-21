#include "../../include/Packet/LOGRQPacket.h"
#include "../../include/MessageEncoderDecoder.h"

LOGRQPacket::LOGRQPacket(const std::string &userName):userName(userName){
    opCode=7;
}

LOGRQPacket::LOGRQPacket(const LOGRQPacket &logRQPacket)
        : userName(logRQPacket.userName){

    Packet::opCode = 3;
}

LOGRQPacket& LOGRQPacket::operator=(const LOGRQPacket &b) {
    userName = b.userName;
    return *this;
}

std::string LOGRQPacket::getUserName() {
    return userName;
}

char * LOGRQPacket::toByteArr()  {

    char opCodeBytes[2];
    returnBytes = new char[2 + userName.length() + 1];

    MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);

    for (unsigned int i = 0; i < 2; i++)
        returnBytes[i] = opCodeBytes[i];

    for (unsigned int i = 2; i < 2 + userName.length(); i++)
        returnBytes[i] = userName.c_str()[i - 2];

    returnBytes[2 + userName.length()] = '\0';

    return returnBytes;
}

LOGRQPacket::~LOGRQPacket() {
    delete(returnBytes);
}

