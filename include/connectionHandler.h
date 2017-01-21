
#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H
                                           
#include <string>
#include <boost/asio.hpp>
#include <iostream>
#include "Packet/Packet.h"
#include "../include/connectionHandler.h"
#include "Packet/LOGRQPacket.h"
#include "Packet/Packet.h"
#include "Packet/RRQPacket.h"
#include "Packet/ACKPacket.h"
#include "Packet/BCASTPacket.h"
#include "Packet/WRQPacket.h"
#include "Packet/ERRORPacket.h"
#include "Packet/DATAPacket.h"
#include "Packet/DELRQPacket.h"
#include "Packet/DIRQPacket.h"
#include "Packet/DISCPacket.h"
#include "MessageEncoderDecoder.h"


using boost::asio::ip::tcp;

class ConnectionHandler {

private:

    const string host_;
	const short port_;
	boost::asio::io_service io_service_;   // Provides core I/O functionality
	tcp::socket socket_;
    MessageEncoderDecoder encDec_;
 
public:

    ConnectionHandler(std::string host, short port, MessageEncoderDecoder encDec);
    virtual ~ConnectionHandler();

    bool connect();
    bool getBytes(char bytes[], unsigned int bytesToRead);
    bool getPacket(Packet* &packet);
    bool getFrameAscii(Packet *&packet);
    bool sendFrameAscii(string &frame, char delimiter);
    bool send(Packet *pPacket);
    bool sendBytes(const char *bytes, int bytesToWrite);
    void close();

};

#endif