#include "BCASTPacket.h"
    BCASTPacket::BCASTPacket(char deletedAdd, const std::wstring &fileName) {
        this->deletedAdd = deletedAdd;
        this->fileName = fileName;
        Packet::opCode = 9;
    }

    char BCASTPacket::getDeletedAdd() {
        return deletedAdd;
    }

    std::wstring BCASTPacket::getFileName() {
        return fileName;
    }

    char* BCASTPacket::toByteArr() {
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + 1 + fileName.length() + 1);
//        lengthBuffer->put(shortToBytes(opCode));
//        lengthBuffer->put(deletedAdd);
//        try {
//            lengthBuffer->put(fileName.getBytes(L"UTF-8"));
//        }
//        catch (const UnsupportedEncodingException &e) {
//            e->printStackTrace();
//        }
//        lengthBuffer->put(static_cast<char>(0));
//        return lengthBuffer->array_Renamed();
    }
