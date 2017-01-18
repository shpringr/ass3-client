#pragma execution_character_set("utf-8")
#pragma once

#include "../include/connectionHandler.h"


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
public:
    static FILE file;
    static Status status;

protected:
    ConnectionHandler connectionHandler;

public:
    void run();

    void process(Packet packet);
};

