#include <iostream>  
#include <boost/thread.hpp>
#include "../include/ListenToKeyboard.h"
#include "../include/ListenToServer.h"

int main(int argc, char *argv[]){

//	if (argc < 3) {
//		std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//		return -1;
//	}
//	std::string host = argv[1];
//	short port = (short) atoi(argv[2]);

	std::string host = "127.0.0.1";
	short port = (short) 7777;


	MessageEncoderDecoder* encoderDecoder = new MessageEncoderDecoder();
	ConnectionHandler connectionHandler(host, port,*encoderDecoder);
	if (!connectionHandler.connect()) {
		std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
		return 1;
	}

	ListenToKeyboard task1(1, &connectionHandler);
	ListenToServer task2(2, &connectionHandler);
	
	boost::thread th1(task1); 
	boost::thread th2(task2); 
	th1.join();
	th2.join();	
	
	return 0;
}
