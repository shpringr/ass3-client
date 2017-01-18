#include <stdlib.h>
#include <iostream>
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



using namespace std;

#include "ListenToKeyboard.h"

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
	
	//From here we will see the rest of the ehco client implementation:
    while (1) {
        Packet answerPacket;
        const short bufsize = 518;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);
        std::string comand(line.substr(0,line.find(" ",0)));
        std::string name(line.substr(line.find("<",0),line.find(">",0)));
        int len=line.length();

        Packet *packetToSend = nullptr;
        ERRORPacket *errorToSend = nullptr;

        if(comand.compare("LOGRQ")){
            packetToSend = new LOGRQPacket(name);
            if (!connectionHandler.send(packetToSend)){
                errorToSend = new ERRORPacket();
                connectionHandler.send();
            }

            connectionHandler.getPacket(answerPacket);



            if(DATAPacket* answerPacket = dynamic_cast<DATAPacket*>(answerPacket)) {
                // old was safely casted to NewType
                //   answerPacket->doSomething();
            }

        }
        else if(comand.compare("DELRQ")){
            packetToSend = new DELRQPacket(name);
            connectionHandler.send(packetToSend);
        }
        else if(comand.compare("WRQ")){
            packetToSend = new WRQPacket(name);
            connectionHandler.send(packetToSend);
        }
        else if(comand.compare("RRQ")){
            packetToSend = new RRQPacket(name);
            connectionHandler.send(packetToSend);
        }
        else if(comand.compare("DIRQ")){
            packetToSend = new DIRQPacket();
            connectionHandler.send(packetToSend);
        }
        else if(comand.compare("DISC")){
            packetToSend = new DISCPacket();
            connectionHandler.send(packetToSend);
        }

        if (!connectionHandler.sendLine(l7ine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
 
        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character

        string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end



        if(ACKPacket* answerPacket = dynamic_cast<ACKPacket*>(answerPacket)) {
            // old was safely casted to NewType
            //answerPacket->doSomething();
        }


        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        
		len=answer.length();

		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len-1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
    return 0;
}
