#include <iostream>
#include "../include/connectionHandler.h"
#include "../include/connectionHandler.h"
#include "../packet/LOGRQPacket.h"
#include "../packet/Packet.h"
#include "../packet/RRQPacket.h"
#include "../packet/ACKPacket.h"
#include "../packet/BCASTPacket.h"
#include "../packet/WRQPacket.h"
#include "../packet/ERRORPacket.h"
#include "../packet/DATAPacket.h"
#include "../packet/DELRQPacket.h"
#include "../packet/DIRQPacket.h"
#include "../packet/DISCPacket.h"
#include "../include/ListenToKeyboard.h"


using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;


ConnectionHandler::ConnectionHandler(std::string host, short port, MessageEncoderDecoder encDec):
host_(host), port_(port), io_service_() , encDec_(encDec), socket_(io_service_)
{}

    
ConnectionHandler::~ConnectionHandler() {
    close();
}
 
bool ConnectionHandler::connect() {
    std::cout << "Starting connect to " 
        << host_ << ":" << port_ << std::endl;
    try {
		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
		boost::system::error_code error;
		socket_.connect(endpoint, error);
		if (error)
			throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getPacket(Packet* packet) {
    return getFrameAscii(packet);

}

bool ConnectionHandler::getFrameAscii(Packet* packet) {
    char ch;
    // Stop when we encounter the null character.
    // Notice that the null character is not appended to the frame string.
    try {
        Packet* packet1 = nullptr;
        while (packet1==nullptr){
            getBytes(&ch, 1);
            packet1 = encDec_.decodeNextByte(ch);
        }
        packet = packet1;
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
			tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);			
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}


bool ConnectionHandler::send(Packet *pPacket) {
    char* encoded = encDec_.encode(pPacket);
    char* tryr =encoded + 1;
    string msg = encoded[0] + tryr;

    char* data = encoded;
    switch(pPacket->getOpCode()){
        case 1: case 2: case 7: case 8: case 5:
            return sendFrameAscii(msg, '\0');
        case 6: case 3: case 4:
            return sendFrameAscii(msg);
        default:
            //TODO: error
            break;
    }
    return false;
}

bool ConnectionHandler::sendFrameAscii(std::string& frame) {
    return sendBytes(frame,frame.length());

}

bool ConnectionHandler::sendFrameAscii(std::string& frame, char delimiter) {
    bool result=sendBytes(frame,frame.length());
    if(!result) return false;
    //return sendBytes(&delimiter,1);
}

bool ConnectionHandler::sendBytes(string &bytes, int bytesToWrite) {
    int tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes, bytesToWrite), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}




// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}
/*

bool ConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\n');
}


bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char ch;
    // Stop when we encounter the null character.
    // Notice that the null character is not appended to the frame string.
    try {
        do{
            getBytes(&ch, 1);
            frame.append(1, ch);
        }while (delimiter != ch);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
*/