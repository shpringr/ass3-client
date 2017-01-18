#include "../include/MessageEncoderDecoder.h"

MessageEncoderDecoder::MessageEncoderDecoder() {
    initAll();
}

void MessageEncoderDecoder::initAll() {
//    initOpObjects();
//    if (lengthBuffer != nullptr) {
//        lengthBuffer->clear();
//    }
//    if (blockBuffer != nullptr) {
//        blockBuffer->clear();
//    }
//    if (packetSizeBuffer != nullptr) {
//        packetSizeBuffer->clear();
//    }
//    if (errorBuffer != nullptr) {
//        errorBuffer->clear();
//    }
    errorCode = -1;
    errorArr.clear();
    packetSizeArr.clear();
    packetSize = 0;
    blockArr.clear();
    block = 0;
    deletedAdd = L'e';
}

void MessageEncoderDecoder::initOpObjects() {
//    if (opLengthBuffer != nullptr) {
//        opLengthBuffer->clear();
//    }
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

    return res;
}

void MessageEncoderDecoder::makeBCastPacket(char nextByte)  {
//    if (deletedAdd == L'e') {
//        deletedAdd = nextByte;
//    } else {
//        if (nextByte != L'\0') {
//            lengthBuffer->put(nextByte);
//        } else { //nextByte == '\0'
//            string fileName = string(getDataFromBuffer(lengthBuffer), L"UTF-8");
//            res = new BCASTPacket(deletedAdd, fileName);
//            initAll();
//        }
//    }
}

void MessageEncoderDecoder::makeDelRqPacket(char nextByte)  {
//    if (nextByte != L'\0') {
//        lengthBuffer->put(nextByte);
//    } else { //nextByte == '\0'
//        string fileName = string(getDataFromBuffer(lengthBuffer), L"UTF-8");
//        res = new DELRQPacket(fileName);
//        initAll();
//    }
}

void MessageEncoderDecoder::makeLoginPacket(char nextByte)  {
//    if (nextByte != L'\0') {
//        lengthBuffer->put(nextByte);
//    } else { //nextByte == '\0'
//        string userName = string(getDataFromBuffer(lengthBuffer), L"UTF-8");
//        res = new LOGRQPacket(userName);
//        initAll();
//    }
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
//            lengthBuffer->put(nextByte);
//        } else { //nextByte == '\0'
//            string errMsg = string(getDataFromBuffer(lengthBuffer), L"UTF-8");
//            res = new ERRORPacket(errorCode, errMsg);
//            initAll();
//        }
//    }
}

void MessageEncoderDecoder::makeACKPacket(char nextByte) {
//    lengthBuffer->put(nextByte);
//    if (!lengthBuffer->hasRemaining()) {
//        short blockAck = bytesToShort(getDataFromBuffer(lengthBuffer));
//        res = new ACKPacket(blockAck);
//        initAll();
//    }
}

void MessageEncoderDecoder::makeDataPacket(char nextByte) {
//    if (packetSizeArr.empty()) {
//        packetSizeBuffer->put(nextByte);
//        if (!packetSizeBuffer->hasRemaining()) {
//            packetSizeArr = getDataFromBuffer(packetSizeBuffer);
//            packetSize = bytesToShort(packetSizeArr);
//        }
//    } else if (blockArr.empty()) {
//        blockBuffer->put(nextByte);
//        if (!blockBuffer->hasRemaining()) {
//            blockArr = getDataFromBuffer(blockBuffer);
//            block = bytesToShort(blockArr);
//        }
//    } else {
//        lengthBuffer->put(nextByte);
//        packetSize--;
//        if (packetSize == 0) {
//            std::vector<char> bytes = getDataFromBuffer(lengthBuffer);
//            res = new DATAPacket(static_cast<short>(bytes.size()), block, bytes);
//            initAll();
//        }
//    }
}

void MessageEncoderDecoder::makeWRQPacket(char nextByte)  {
//    if (nextByte != L'\0') {
//        lengthBuffer->put(nextByte);
//    } else { //nextByte == '\0'
//        string filename = string(getDataFromBuffer(lengthBuffer), L"UTF-8");
//        res = new WRQPacket(filename);
//        initAll();
//    }
}

void MessageEncoderDecoder::makeRRQPacket(char nextByte)  {
//    if (nextByte != L'\0') {
//        lengthBuffer->put(nextByte);
//    } else { //nextByte == '\0'
//        string filename = string(getDataFromBuffer(lengthBuffer), L"UTF-8");
//        res = new RRQPacket(filename);
//        initAll();
//    }
}

void MessageEncoderDecoder::initOpCodeAndBuffers(char nextByte) {
//    opLengthBuffer->put(nextByte);
//    if (!opLengthBuffer->hasRemaining()) {
//        opCode = bytesToShort(getDataFromBuffer(opLengthBuffer));
//        switch (opCode) {
//            case 1 :
//            case 2 :
//            case 7:
//            case 8:
//            case 9:
//                lengthBuffer = ByteBuffer::allocate(516);
//                break;
//            case 3:
//                packetSizeBuffer = ByteBuffer::allocate(2);
//                blockBuffer = ByteBuffer::allocate(2);
//                lengthBuffer = ByteBuffer::allocate(512);
//                break;
//            case 4:
//                lengthBuffer = ByteBuffer::allocate(2);
//                break;
//            case 5:
//                errorBuffer = ByteBuffer::allocate(2);
//                lengthBuffer = ByteBuffer::allocate(516);
//                break;
//            case 6:
//                res = new DIRQPacket();
//                initOpObjects();
//                break;
//
//            case 10:
//                res = new DISCPacket();
//                initOpObjects();
//                break;
//        }
//    }/
}

char* MessageEncoderDecoder::encode(Packet *message) {
    char* outStr;
    message->toByteArr(outStr);
    return outStr;

}

short MessageEncoderDecoder::bytesToShort(char bytesArr[]) {
    short result = (short) ((bytesArr[0] & 0xff) << 8);
    result += (short) (bytesArr[1] & 0xff);
    return result;
}

void MessageEncoderDecoder::shortToBytes(short num, char bytesArr[]) {
    bytesArr[0] = (char) ((num >> 8) & 0xFF);
    bytesArr[1] = (char) (num & 0xFF);
}
