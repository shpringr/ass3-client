#include "ERRORPacket.h"

    ERRORPacket::ERRORPacket(short errorCode, const string &errMsg) {
        this->errorCode = errorCode;
        this->errMsg = errMsg;
        Packet::opCode = 5;
    }

    short ERRORPacket::getErrorCode() {
        return errorCode;
    }

    string ERRORPacket::getErrMsg() {
        return errMsg;
    }

    char * ERRORPacket::toByteArr()  {

        char *opCodeBytes = new char[2];
        char *errorCodeChar = new char[2];
        const char *errorMsgChar = errMsg.c_str();
        char *returnBytes = new char[2 + 2+ errMsg.length() + 1];

        shortToBytes(opCode, opCodeBytes);
        shortToBytes(errorCode, errorCodeChar);

        for (unsigned int i = 0; i < 2; i++)
            returnBytes[i] = opCodeBytes[i];

        for (unsigned int i = 2; i < 4; i++)
            returnBytes[i] = errorCodeChar[i-2];

        for (unsigned int i = 4; i < sizeof(returnBytes) - 1; i++)
            returnBytes[i] = errorMsgChar[i - 4];

        returnBytes[sizeof(returnBytes) - 1] = '\0';

        return returnBytes;
    }

