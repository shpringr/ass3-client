#pragma execution_character_set("utf-8")
#pragma once
#include <fstream>
#include <iostream>

#include "../include/connectionHandler.h"


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
public:
    ofstream fileToWrite;
    ifstream fileTosend;
    static Status status;
    static string fileName;

protected:
    ConnectionHandler connectionHandler;

public:
    void run();

    void process(Packet* packet);

    void handleAckPacket(ACKPacket *message);

    void handleDataPacket(DATAPacket *message);

    void handleErrorPacket(ERRORPacket *packet);

    void handleBCastPacket(BCASTPacket *packet);
};

