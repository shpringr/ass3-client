#include <cstring>
#include "../include/MessageEncoderDecoder.h"
#include "../packet/DIRQPacket.h"
#include "../packet/DISCPacket.h"
#include "../packet/ACKPacket.h"
#include "../packet/DATAPacket.h"
#include "../packet/LOGRQPacket.h"
#include "../packet/BCASTPacket.h"
#include "../packet/DELRQPacket.h"

MessageEncoderDecoder::MessageEncoderDecoder() {
    initAll();
}

void MessageEncoderDecoder::initAll() {
    initOpObjects();

    lengthArr = nullptr;
    lengthArrSize=0;
    lengthArrIndex=0;

    errorArr= nullptr;
    errorArrSize=0;
    errorArrIndex=0;

    errorCode = -1;

    packetArr= nullptr;
    packetArrSize=0;
    packetArrIndex=0;

    packetSize = 0;

    blockArr = nullptr;
    blockArrSize=0;
    blockArrIndex=0;

    block = 0;

    deletedAdd = L'e';
}

void MessageEncoderDecoder::initOpObjects() {
    opCode = 0;
}

Packet *MessageEncoderDecoder::decodeNextByte(char nextByte)  {
    switch (opCode) {
        case 0:
            initOpCodeAndBuffers(nextByte);
            break;

        case 1:
            makeRRQPacket(nextByte);
            break;

        case 2:
            makeWRQPacket(nextByte);
            break;

        case 3:
            makeDataPacket(nextByte);
            break;

        case 4:
            makeACKPacket(nextByte);
            break;

        case 5:
            makeErrorPacket(nextByte);
            break;

        case 6:
            break;

        case 7:
            makeLoginPacket(nextByte);
            break;

        case 8:
            makeDelRqPacket(nextByte);
            break;

        case 9:
            makeBCastPacket(nextByte);
            break;

        case 10:
            break;

        default:break;
    }

    Packet* tmp = res;
    res = nullptr;
    return tmp;
}

void MessageEncoderDecoder::makeBCastPacket(char nextByte)  {

    if (deletedAdd == L'e') {
        deletedAdd = nextByte;
    } else {
        if (nextByte != L'\0') {
            lengthArr[lengthArrIndex] = nextByte;
            lengthArrIndex++;
        } else { //nextByte == '\0'
            lengthArr[lengthArrIndex] = nextByte;
            string fileName = lengthArr;
            res = new BCASTPacket(deletedAdd, fileName);
            initAll();
        }
    }
}

void MessageEncoderDecoder::makeDelRqPacket(char nextByte)  {
        if (nextByte != L'\0') {
            lengthArr[lengthArrIndex] = nextByte;
            lengthArrIndex++;
        } else { //nextByte == '\0'
            lengthArr[lengthArrIndex] = nextByte;
            string fileName = lengthArr;
            res = new DELRQPacket(fileName);
            initAll();
        }
}

void MessageEncoderDecoder::makeLoginPacket(char nextByte)  {
    if (nextByte != L'\0') {
        lengthArr[lengthArrIndex] = nextByte;
        lengthArrIndex++;
    }
    else
    {
        lengthArr[lengthArrIndex] = nextByte;
        string userName = lengthArr;
        res = new LOGRQPacket(userName);
        initAll();
    }
}

//std::vector<char> MessageEncoderDecoder::getDataFromBuffer(ByteBuffer *buffer) {
//    buffer->flip();
//    std::vector<char> objectBytes(buffer->limit());
//    buffer->get(objectBytes, 0, buffer->limit());
//    return objectBytes;
//}

void MessageEncoderDecoder::makeDIRQPacket() {
//    res = new DIRQPacket();
//    initAll();
}

void MessageEncoderDecoder::makeErrorPacket(char nextByte)  {
//    if (errorArr.empty()) {
//        errorBuffer->put(nextByte);
//        if (!errorBuffer->hasRemaining()) {
//            errorArr = getDataFromBuffer(errorBuffer);
//            errorCode = bytesToShort(errorArr);
//        }
//    } else {
//        if (nextByte != L'\0') {
//            lengthArr->put(nextByte);
//        } else { //nextByte == '\0'
//            string errMsg = string(getDataFromBuffer(lengthArr), L"UTF-8");
//            res = new ERRORPacket(errorCode, errMsg);
//            initAll();
//        }
//    }
}

void MessageEncoderDecoder::makeACKPacket(char nextByte) {
    lengthArr[lengthArrIndex]=nextByte;

    if (lengthArrIndex == lengthArrSize - 1) {
        short blockAck = bytesToShort(lengthArr);
        res = new ACKPacket(blockAck);
        initAll();
    }
    else
    {
        lengthArrIndex++;
    }
}

void MessageEncoderDecoder::makeDataPacket(char nextByte) {
    if (packetArrIndex != packetArrSize) {
        packetArr[packetArrIndex]=nextByte;
        packetArrIndex++;
        if (packetArrIndex == packetArrSize) {
            packetSize = bytesToShort(packetArr);
        }
    }
    else if (blockArrIndex != blockArrSize) {
        blockArr[blockArrIndex]=nextByte;
        blockArrIndex++;
        if (blockArrIndex== blockArrSize) {
            block = bytesToShort(blockArr);
        }
    } else {
        lengthArr[lengthArrIndex]=nextByte;
        packetSize--;
        lengthArrIndex++;
        if (packetSize == 0) {
            lengthArr[lengthArrIndex] = '\0';
            res = new DATAPacket(lengthArrIndex, block, lengthArr);
            initAll();
        }
    }
}

void MessageEncoderDecoder::makeWRQPacket(char nextByte)  {
//    if (nextByte != L'\0') {
//        lengthArr->put(nextByte);
//    } else { //nextByte == '\0'
//        string filename = string(getDataFromBuffer(lengthArr), L"UTF-8");
//        res = new WRQPacket(filename);
//        initAll();
//    }
}

void MessageEncoderDecoder::makeRRQPacket(char nextByte)  {
//    if (nextByte != L'\0') {
//        lengthArr->put(nextByte);
//    } else { //nextByte == '\0'
//        string filename = string(getDataFromBuffer(lengthArr), L"UTF-8");
//        res = new RRQPacket(filename);
//        initAll();
//    }
}

void MessageEncoderDecoder::initOpCodeAndBuffers(char nextByte) {

    if (nextByte != 0)
    {
        opCode = bytesToShort(new char[2]{0,nextByte});
        switch (opCode) {
            case 1 :
            case 2 :
            case 7:
            case 8:
            case 9:
                lengthArrSize = 516;
                lengthArr = new char[lengthArrSize];
                break;
            case 3:
                packetArrSize = 2;
                packetArr = new char[packetArrSize];
                blockArrSize =2;
                blockArr = new char[blockArrSize];
                lengthArrSize = 516;
                lengthArr = new char[lengthArrSize];
                break;
            case 4:
                lengthArrSize = 2;
                lengthArr = new char[lengthArrSize];
                break;
            case 5:
                errorArrSize = 2;
                errorArr = new char[errorArrSize];
                lengthArrSize = 516;
                lengthArr = new char[lengthArrSize];
                break;
            case 6:
                res = new DIRQPacket();
                initOpObjects();
                break;

            case 10:
                res = new DISCPacket();
                initOpObjects();
                break;
        }
    }
}

char* MessageEncoderDecoder::encode(Packet *message) {
    return message->toByteArr();
}

void MessageEncoderDecoder::shortToBytes(short num, char *bytesArr) {

    bytesArr[0] = (char) ((num >> 8) & 0xFF);
    bytesArr[1] = (char) (num & 0xFF);
}

short MessageEncoderDecoder::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}