#include <boost/asio/buffer.hpp>
#include "ACKPacket.h"
    ACKPacket::ACKPacket(short block) {
        this->block = block;
        Packet::opCode = 4;
    }

    short ACKPacket::getBlock() {
        return block;
    }

    char* ACKPacket::toByteArr() {
//        size_t tmp = 0;
//        boost::system::error_code error;
//        try {
//            while (!error && bytesToRead > tmp ) {
//                tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);
//            }
//            if(error)
//                throw boost::system::system_error(error);
//        } catch (std::exception& e) {
//            std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
//            return f  alse;
//        }
//        return true;
//
        char *opCodeBytes = new char[2];
        char *blockBytes = new char[2];

        shortToBytes(opCode, opCodeBytes);
        shortToBytes(block, blockBytes);

        return strcat(opCodeBytes, blockBytes);
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + 2);
//        lengthBuffer->put(shortToBytes(opCode));
//        lengthBuffer->put(shortToBytes(block));
//        return leng/thBuffer->array_Renamed();
    }
