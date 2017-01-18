//
// Created by ROTEM on 18/01/2017.
//


#include "../include/connectionHandler.h"


enum class Status {
    Normal=0,
    RRQ,
    WRQ,
    DATA,
    ACK,
    ERROR,
    DIRQ ,
    LOGRQ,
    DELRQ,
    BCAST,
    DISC
};

class ListenToServer {
public:
    static Status status;

protected:
    ConnectionHandler connectionHandler;

public:
    void run(Packet);
};

