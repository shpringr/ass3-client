#pragma execution_character_set("utf-8")

#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "BidiMessagingProtocol.h"
#include <string>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>

using namespace bgu::spl171::net::impl::packet;


class BidiMessagingProtocolImpl {

private:
    static constexpr short ACK_OK = 0;
    static std::vector<int> logOns;
    static File *const file = new File(L"Server/Files");

//JAVA TO C++ CONVERTER NOTE: Fields cannot have the same name as methods:
    bool shouldTerminate_Renamed = false;
    Connections *connections;
    boost::optional<int> connectionId;
    bool isFirstCommand = true;
    LinkedBlockingQueue<DATAPacket *> *dataQueue = new LinkedBlockingQueue<DATAPacket *>();
    std::wstring state = L"";
    File *fileToWrite = nullptr;

public:
    virtual ~BidiMessagingProtocolImpl() {
        delete connections;
        delete dataQueue;
        delete fileToWrite;
    }

    virtual void start(int connectionId, Connections *connections) override;

    virtual void process(Packet *message) override;

private:
    void handleDiscPacket();

    void handleBCastPacket();

    void handleErrorPacket();

    void handleAckPacket(ACKPacket *message);

    void handleDataPacket(DATAPacket *message);

    void handleWritePacket(WRQPacket *message);

    void handleReadPacket(RRQPacket *message);

    bool isLegalFirstCommand(Packet *message);

    void handleDirqPacket();

    void handleDelReqPacket(DELRQPacket *message);

    void broadcastMessageToLogons(char delOrIns, const std::wstring &filename);

    void sendError(ERRORPacket::Errors *errorCode, const std::wstring &extraMsg);

    void handleLoginPacket(LOGRQPacket *message);

    void readFileIntoDataQueue(File *file) throw(IOException);

public:
    virtual bool shouldTerminate() override;
};
