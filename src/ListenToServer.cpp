#include <boost/thread/win32/thread_data.hpp>
#include <codecvt>
#include "../include/ListenToServer.h"


Status ListenToServer::status(Status::Normal);
string ListenToServer::fileName("");
bool ListenToServer::connected = true;


ListenToServer::ListenToServer(const ListenToServer& listenToServer){
    _id = listenToServer._id;
    connectionHandler = listenToServer.connectionHandler;
}

ListenToServer::ListenToServer(int number, shared_ptr<ConnectionHandler> handler)
{
    connectionHandler=handler;
    _id=number;
    //dataQueue = queue<DATAPacket *>();
}

void ListenToServer::run() {
    while (connected) {
        Packet* answerPacket = nullptr;

        if (connectionHandler->getPacket(answerPacket)) {
            process(answerPacket);
        } else {
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
                connectionHandler->send(dataQueue.front());
                dataQueue.pop();

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
    }
}

void ListenToServer::handleDataPacket(DATAPacket *message) {
    switch (ListenToServer::status){
        case Status::RRQ:
            ListenToServer::fileToWrite.open("./" + fileName);
            if (ListenToServer::fileToWrite.is_open()) {
                ListenToServer::fileToWrite.write(message->getData(), message->getPacketSize());
                connectionHandler->send(new ACKPacket(message->getBlock()));
            } else{
                connectionHandler->send(new ERRORPacket(1,""));
            }

            if (message->getPacketSize()!=512){
                ListenToServer::fileToWrite.close();
                std::cout << "RRQ " << fileName << " complete" <<  std::endl;
                ListenToServer::status = Status::Normal;
            }
            break;
            //
        case Status::DIRQ:

            for (int i = 0; i <= message->packetSize; ++i)
            {
                dirqCharArr[(message->getBlock() - 1)*512 + i] = message->getData()[i];
            }

            if (message->getPacketSize() < 512)
            {
                printDirqArr((message->getPacketSize() + (message->getBlock() - 1)*512));
                Status::Normal;
                connectionHandler->send(new ACKPacket(message->getBlock()));
            }
            //TODO

            //handleAckPacket(static_cast<ACKPacket *>());
            break;
    }
}



void ListenToServer::readFileIntoDataQueue(){

    ListenToServer::fileTosend= ifstream(fileName, ios::in|ios::binary|ios::ate);

    //TODO : RELATIVE PATH
    ListenToServer::fileTosend.open("C:\\Users\\Orel Hazan\\Documents\\studies\\spl\\ass3\\Client\\src\\" + fileName);
//TODO: utf-8
//    const std::locale empty_locale;
//    typedef std::codecvt_utf8<wchar_t> converter_type;
//    const converter_type* converter = new converter_type;
//    const std::locale utf8_locale = std::locale(empty_locale, converter);
//
//    fileTosend.imbue(utf8_locale);

    if (ListenToServer::fileTosend.is_open()) {
        char getdata[512];

        while (!fileTosend.eof()) {
            fileTosend.read(getdata, sizeof getdata);
            int bytes_really_read = 512;

            if (fileTosend.eof()) {
                bytes_really_read = fileTosend.gcount();
            } else if (fileTosend.fail()) {
                bool fsd = true;
                // some other error...
            }

            short numberOfBlocks = (short) ((bytes_really_read / 512) + 1);
            short sizeOfLastBlock = (short) (bytes_really_read % 512);
            if (sizeOfLastBlock == 0 && bytes_really_read > 0)
                sizeOfLastBlock = 512;

            for (short i = 1; i <= numberOfBlocks; ++i) {
                short packetSize = 512;

                if (i == numberOfBlocks) {
                    packetSize = sizeOfLastBlock;
                }

                char *data = getdata + ((i - 1) * 512);

                ListenToServer::dataQueue.push(new DATAPacket(packetSize, i, data));


            }
        }
    }
    else
    {
        connectionHandler->send(new ERRORPacket(1, "no file to write. stop."));
    }
}

void ListenToServer::operator()(){
    run();
    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}

void ListenToServer::printDirqArr(int size) {

    string str = dirqCharArr;
    int currSize = 0;

    while(currSize <= size)
    {
        cout << str << endl;
        currSize += str.length()+1;
        str = dirqCharArr + currSize;
    }}

ListenToServer::~ListenToServer() {
    //connectionHandler;
    fileToWrite.clear();
    fileToWrite.close();
    fileTosend.clear();
    fileTosend.close();
//TODO DIRQ DOESNT WORK WITH THAT
    //delete fileCharArr;
   // delete dirqCharArr;
}


