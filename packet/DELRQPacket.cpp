#include "DELRQPacket.h"

    DELRQPacket::DELRQPacket(const string &filename) {
        fileName = filename;
        Packet::opCode = 8;
    }

    string DELRQPacket::getFilename() {
        return fileName;
    }

    char* DELRQPacket::toByteArr() {
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + getFilename().length() + 1);
//        lengthBuffer->put(shortToBytes(opCode));
//        try {
//            lengthBuffer->put(fileName.getBytes(L"UTF-8"));
//        }
//        catch (const UnsupportedEncodingException &e) {
//            e->printStackTrace();
//        }
//        lengthBuffer->put(static_cast<char>(0));
//        return lengthBuffer->array_Renamed();
    }

