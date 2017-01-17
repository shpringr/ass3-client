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
        char* returnBytes = new char[2+2];

        shortToBytes(opCode, opCodeBytes);
        shortToBytes(opCode, blockBytes);

        for (unsigned int i=0; i< 2; i++)
        {
            returnBytes[i] = opCodeBytes[i];
        }

        for (unsigned int i=2; i< 4; i++)
        {
            returnBytes[i] = blockBytes[i-2];
        }

        return returnBytes;
//        ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + 2);
//        lengthBuffer->put(shortToBytes(opCode));
//        lengthBuffer->put(shortToBytes(block));
//        return leng/thBuffer->array_Renamed();
    }
