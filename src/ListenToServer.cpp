#include <boost/thread/win32/thread_data.hpp>
#include <codecvt>
#include "../include/ListenToServer.h"

Status ListenToServer::status(Status::Normal);
string ListenToServer::fileName("");
bool ListenToServer::connected = true;

ListenToServer::ListenToServer(const ListenToServer& listenToServer)
        :connectionHandler(listenToServer.connectionHandler),
        fileToWrite(), fileToSend(),
         dirqCharArr(), dataQueue()
        {}
ListenToServer::ListenToServer(shared_ptr<ConnectionHandler> handler) : connectionHandler(handler)
,fileToWrite(), fileToSend(),
dirqCharArr(), dataQueue(){}

void ListenToServer::run() {
    while (connected) {
        Packet* answerPacket = nullptr;

        if (connectionHandler->getPacket(answerPacket)) {
            process(answerPacket);
        } else {
            //TODO delete every place the errorpacket appears the couts
            std::cout << "can't get pocket " << fileName << std::endl;
            connectionHandler->send(new ERRORPacket(0,""));
            connected = false;
            }
    }
    cout << "disconnected server!"<<endl;
}

void ListenToServer::process(Packet* packet) {
    switch ((packet->getOpCode())) {
        case 3:
            handleDataPacket(static_cast<DATAPacket *>(packet));
            break;
        case 4:
            handleAckPacket(static_cast<ACKPacket *>(packet));
            break;
        case 5:
            handleErrorPacket(static_cast<ERRORPacket *>(packet));
            break;
        case 9:
            handleBCastPacket(static_cast<BCASTPacket *>(packet));
            break;
        default:
            //TODO sendError(ERRORPacket::Errors::ILLEGAL_TFTP_OPERATION, L"");
            cout << "Error 4" << endl;
            break;
    }
}

void ListenToServer::handleBCastPacket(BCASTPacket *packet) {
    if(packet->getDeletedAdd()==1){
        std::cout << "BCAST add " << packet->getFileName() <<  std::endl;
    }
    else if(packet->getDeletedAdd()==0){
        std::cout << "BCAST del " << packet->getFileName()  <<  std::endl;
    }
}

void ListenToServer::handleErrorPacket(ERRORPacket* packet) {
    //TODO:change to code
    std::cout << "Error " << packet->getErrMsg()  <<  std::endl;
}

void ListenToServer::handleAckPacket(ACKPacket *message) {
    std::cout << "ACK " << message->getBlock() <<  std::endl;
    switch (ListenToServer::status){
        case Status::LOGRQ:
            ListenToServer::status = Status::Normal;
            break;
        case Status::WRQ:
            if(message->getBlock()==0) {
                readFileIntoDataQueue();
                if (!dataQueue.empty()) {
                    DATAPacket* dataPacket = dataQueue.front();
                    connectionHandler->send(dataPacket);
                    dataQueue.pop();
                }
            }
            else if(!dataQueue.empty()) {
                    connectionHandler->send(dataQueue.front());
                    dataQueue.pop();
            }
            else{
                std::cout << "WRQ " << fileName << " complete" <<  std::endl;
                ListenToServer::status = Status::Normal;
            }
            break;
        case Status::DISC:
            connectionHandler->send(new ACKPacket(0));
             break;
        default:
            connectionHandler->send(new ERRORPacket(0, ""));
    }
}

void ListenToServer::handleDataPacket(DATAPacket *message) {
    switch (ListenToServer::status) {
        case Status::RRQ: {

            if (message->getPacketSize() != 0) {
                string fullFileName = "./" + fileName;


                if (message->getBlock() != 1)
                    fileToWrite.open(fullFileName, ios::app | ios::binary);
                else
                    fileToWrite.open(fullFileName, ios::binary);

                if (ListenToServer::fileToWrite.is_open()) {
                    ListenToServer::fileToWrite.write(message->getData(), message->getPacketSize());
                    connectionHandler->send(new ACKPacket(message->getBlock()));
                    ListenToServer::fileToWrite.close();
                } else {
                    std::cout << "can't write file to server" << fileName << std::endl;
                    connectionHandler->send(new ERRORPacket(1, ""));
                }
            }

            if (message->getPacketSize() != 512) {
                std::cout << "RRQ " << fileName << " complete" << std::endl;
                ListenToServer::status = Status::Normal;
            }
        }
            break;
            //
        case Status::DIRQ:

            for (int i = 0; i <= message->packetSize; ++i) {
                dirqCharArr.push_back(message->getData()[i]);
            }

            if (message->getPacketSize() < 512) {
                printDirqArr((message->getPacketSize() + (message->getBlock() - 1) * 512));
                status = Status::Normal;
                connectionHandler->send(new ACKPacket(message->getBlock()));
            }
            break;
        default:
            break;
    }
}



void ListenToServer::readFileIntoDataQueue(){

    try {
        string fullFileName = "./" + fileName;
        fileToSend.open(fileName, ios::binary | ios::app);

        if (ListenToServer::fileToSend.is_open()) {
            vector<char>* getData;
            int bytes_really_read =512;
            short blockNumber = 0;

            while (!fileToSend.eof()) {
                getData = new vector<char>(512);
                fileToSend.read(getData->data(), bytes_really_read);

                if (fileToSend.eof()) {
                    bytes_really_read = fileToSend.gcount();
                }

                blockNumber++;

                char* data = getData->data();
                ListenToServer::dataQueue.push(
                        new DATAPacket((short) bytes_really_read, blockNumber, data));

            }

            fileToSend.close();
        } else {
            std::cout << "can't read file from client " << fileName << std::endl;
            connectionHandler->send(new ERRORPacket(1, "no file to write. stop."));
        }
    }
    catch (std::ios_base::failure& e) {
        std::cerr << e.what() << '\n';
    }
}

void ListenToServer::operator()(){
    run();
    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}

void ListenToServer::printDirqArr(int size) {

    string str = string(&dirqCharArr[0]);

    int currSize = 0;

    while (currSize <= size) {
        cout << str << endl;
        currSize += str.length() + 1;
        str = string(&dirqCharArr[currSize]);
    }
}

ListenToServer::~ListenToServer() {
    //connectionHandler;
    fileToWrite.clear();
    fileToWrite.close();
    fileToSend.clear();
    fileToSend.close();
//TODO DIRQ DOESNT WORK WITH THAT
    //delete fileCharArr;
   // delete dirqCharArr;
}