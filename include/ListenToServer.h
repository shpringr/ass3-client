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
    shared_ptr<ConnectionHandler> connectionHandler;
    ofstream fileToWrite;
    ifstream fileTosend;
    std::vector<char> dirqCharArr;
    queue <DATAPacket *> dataQueue ;

public:
    static bool connected;
    static Status status;
    static string fileName;

    ListenToServer(shared_ptr<ConnectionHandler> handler);
    ListenToServer(const ListenToServer &listenToServer_);
    ~ListenToServer();
    void operator()();

    void run();

    void process(Packet* packet);

    void handleAckPacket(ACKPacket *message);

    void handleDataPacket(DATAPacket *message);

    void handleErrorPacket(ERRORPacket *packet);

    void handleBCastPacket(BCASTPacket *packet);

    void readFileIntoDataQueue();

    void printDirqArr(int size);
};