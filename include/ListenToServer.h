#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "connectionHandler.h"

enum class Status {
    Normal=0,
    RRQ = 1,
    WRQ =2,
    DATA = 3,
    ACK =4,
    ERRORR = 5,
    DIRQ =6,
    LOGRQ =7,
    DELRQ = 8,
    BCAST = 9,
    DISC =10
};


class ListenToServer {
protected:
    int _id;
    shared_ptr<ConnectionHandler> connectionHandler;
public:
    ofstream fileToWrite;
    ifstream fileTosend;
    static Status status;
    static string fileName;
    queue <DATAPacket *> dataQueue ;
    char *fileCharArr;
    std::vector<char> dirqCharArr;
    // stirng s = string(&vec[0])

    ListenToServer(int number, shared_ptr<ConnectionHandler> handler);
    ListenToServer(const ListenToServer &listenToServer_);

    ~ListenToServer();

    void run();
    void process(Packet* packet);

    void handleAckPacket(ACKPacket *message);

    void handleDataPacket(DATAPacket *message);

    void handleErrorPacket(ERRORPacket *packet);

    void handleBCastPacket(BCASTPacket *packet);
    void operator()();

    void readFileIntoDataQueue();

    static bool connected;

    void printDirqArr(int size);

    std::string getString(const std::string& fullString);

};