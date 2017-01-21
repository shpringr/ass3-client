#include "../../include/Packet/ERRORPacket.h"
#include "../../include/MessageEncoderDecoder.h"

ERRORPacket::ERRORPacket(short errorCode, const string &errMsg) :
errorCode(errorCode),errMsg(errMsg)
{
        Packet::opCode = 5;
    }

ERRORPacket::ERRORPacket(const ERRORPacket& errPacket)
        : errorCode(errPacket.errorCode), errMsg(errPacket.errMsg){
    Packet::opCode = 3;
}

ERRORPacket& ERRORPacket::operator=(const ERRORPacket&b) {
    errorCode = b.errorCode;
    errMsg= b.errMsg;
    return *this;
}

    short ERRORPacket::getErrorCode() {
        return errorCode;
    }

const char* ERRORPacket::getErrorCodeInBytes() {
    char *errorCodeArr = new char[2];
    MessageEncoderDecoder::shortToBytes(getErrorCode(),errorCodeArr);
    return errorCodeArr;
}

    string ERRORPacket::getErrMsg() {
        return errMsg;
    }

    char * ERRORPacket::toByteArr()  {

        char opCodeBytes[2];
        char errorCodeChar[2];
        returnBytes = new char[2 + 2+ errMsg.length() + 1];

        MessageEncoderDecoder::shortToBytes(opCode, opCodeBytes);
        MessageEncoderDecoder::shortToBytes(errorCode, errorCodeChar);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 4; i++)
            returnBytes[i] = errorCodeChar[i-2];

        for (unsigned int i = 4; i < 2 + 2+ errMsg.length(); i++)
            returnBytes[i] = errMsg.c_str()[i - 4];

        returnBytes[2 + 2+ errMsg.length()] = '\0';

        return returnBytes;
    }

ERRORPacket::~ERRORPacket() {

    delete(returnBytes);
}

