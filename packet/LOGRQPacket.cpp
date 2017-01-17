#include "LOGRQPacket.h"

    LOGRQPacket::LOGRQPacket(const std::string &userName) {
        this->userName = userName;
        Packet::opCode = 7;
    }

    std::string LOGRQPacket::getUserName() {
        return userName;
    }

    std::vector<char> LOGRQPacket::toByteArr() {
//						ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + getUserName().length() + 1);
//						lengthBuffer->put(shortToBytes(opCode));
//						try
//						{
//							lengthBuffer->put(userName.getBytes(L"UTF-8"));
//						}
////						catch (const UnsupportedEncodingException &e)
//						{
//							e->printStackTrace();
//						}
//						lengthBuffer->put(static_cast<char>(0));
//						return lengthBuffer->array_Renamed();
    }

