#pragma execution_character_set("utf-8")
#pragma once

#include "connectionHandler.h"


enum class Status {
    Normal=0,
    RRQ,
    WRQ,
    DATA,
    ACK,
    ERRORR,
    DIRQ ,
    LOGRQ,
    DELRQ,
    BCAST,
    DISC
};


class ListenToServer {
protected:
    int _id;
    ConnectionHandler* connectionHandler = nullptr;
public:
    static FILE file;
    static Status status;

    ListenToServer(int number, ConnectionHandler* handler);
    void run();
    void process(Packet* packet);
    void operator()();
};

