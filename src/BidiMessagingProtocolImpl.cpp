#include "../include/BidiMessagingProtocolImpl.h"
#include "Connections.h"

using namespace bgu::spl171::net::impl::packet;
//					import static bgu.spl171.net.impl.packet.ERRORPacket.Errors.*;
std::vector<int> BidiMessagingProtocolImpl::logOns;

void BidiMessagingProtocolImpl::start(int connectionId, Connections *connections) {
    this->connections = connections;
    this->connectionId = connectionId;
}

void BidiMessagingProtocolImpl::process(Packet *message) {

    if (isLegalFirstCommand(message)) {
        switch ((message->getOpCode())) {
            case 1:
                handleReadPacket(static_cast<RRQPacket *>(message));
                break;

            case 2:
                handleWritePacket(static_cast<WRQPacket *>(message));
                break;

            case 3:
                handleDataPacket(static_cast<DATAPacket *>(message));
                break;

            case 4:
                handleAckPacket(static_cast<ACKPacket *>(message));
                break;

            case 5:
                handleErrorPacket();
                break;

            case 6:
                handleDirqPacket();
                break;

            case 7:
                handleLoginPacket(static_cast<LOGRQPacket *>(message));
                break;

            case 8:
                handleDelReqPacket(static_cast<DELRQPacket *>(message));
                break;

            case 9:
                handleBCastPacket();
                break;

            case 10:
                handleDiscPacket();
                break;
            default:
                sendError(ERRORPacket::Errors::ILLEGAL_TFTP_OPERATION, L"");
                break;
        }
    }
}

void BidiMessagingProtocolImpl::handleDiscPacket() {
    try {
        connections->disconnect(connectionId);
//JAVA TO C++ CONVERTER TODO TASK: The Java Collection 'remove(Object)' method is not converted:
        logOns.remove(connectionId);
        ACKPacket tempVar(ACK_OK);
        connections->send(connectionId, &tempVar);
        shouldTerminate_Renamed = true;
    }
    catch (const IOException &e) {
        sendError(ERRORPacket::Errors::NOT_DEFINED, e->getMessage());
    }
}

void BidiMessagingProtocolImpl::handleBCastPacket() {
    sendError(ERRORPacket::Errors::NOT_DEFINED, L"called BCast on server side!");
}

void BidiMessagingProtocolImpl::handleErrorPacket() {
    sendError(ERRORPacket::Errors::NOT_DEFINED, L"called BCast on error side!");
}

void BidiMessagingProtocolImpl::handleAckPacket(ACKPacket *message) {
    if (message->getBlock() != 0) {
        if (state == L"reading") {
            DATAPacket *dataToSend = dataQueue->poll();
            if (dataToSend != nullptr) {
                connections->send(connectionId, dataToSend);
            } else {
                state = L"";
                dataQueue->clear();
            }
        }
    }
}

void BidiMessagingProtocolImpl::handleDataPacket(DATAPacket *message) {
    if (state == L"writing") {
        try {
            FileOutputStream *fileOutputStream = new FileOutputStream(fileToWrite);
            fileOutputStream->write(message->getData());
            ACKPacket tempVar(message->getBlock());
            connections->send(connectionId, &tempVar);

            if (message->getPacketSize() != 512) {
                delete fileOutputStream;
                broadcastMessageToLogons(static_cast<char>(1), fileToWrite->getName());
                state = L"";
            }
        }
        catch (const FileNotFoundException &e) {
            sendError(FILE_NOT_FOUND, L"");
        }
        catch (const IOException &e) {
            sendError(NOT_DEFINED, e->getMessage());
        }
    }
}

void BidiMessagingProtocolImpl::handleWritePacket(WRQPacket *message) {
    std::wstring fileNameToWrite = message->getFileName();

    // create new file
    fileToWrite = new File(file->getPath() + std::wstring(L"/") + fileNameToWrite);
    // tries to create new file in the system
    try {
        bool createFile = fileToWrite->createNewFile();
        if (createFile) {
            ACKPacket tempVar(ACK_OK);
            connections->send(connectionId, &tempVar);
            state = L"writing";
        } else {
            sendError(ERRORPacket::Errors::FILE_ALREADY_EXISTS, L"");
        }
    }
    catch (const IOException &e) {
        sendError(NOT_DEFINED, e->getMessage());

    }
    catch (const SecurityException &e) {
        sendError(ERRORPacket::Errors::ACCESS_VIOLATION, L"");
    }
}

void BidiMessagingProtocolImpl::handleReadPacket(RRQPacket *message) {
    std::wstring fileName = message->getFileName();
    bool isFileFound = false;
    try {
        if (file->listFiles() != nullptr) {
            for (File *file : file->listFiles()) {
                if (fileName == file->getName()) {
                    state = L"reading";
                    isFileFound = true;
                    try {
                        readFileIntoDataQueue(file);
                        //send the first packet
                        DATAPacket *dataToSend = dataQueue->poll();
                        if (dataToSend != nullptr) {
                            connections->send(connectionId, dataToSend);
                        }
                    }
                    catch (const IOException &e) {
                        sendError(NOT_DEFINED, e->getMessage());
                    }
                    break;
                }

            }
        }

        if (!isFileFound) {
            sendError(FILE_NOT_FOUND, L"");
        }
    }
    catch (const SecurityException &e) {
        sendError(ERRORPacket::Errors::ACCESS_VIOLATION, L"");
    }

}

bool BidiMessagingProtocolImpl::isLegalFirstCommand(Packet *message) {
    if (isFirstCommand) {
        isFirstCommand = false;

        if (message->getOpCode() != 7) {
            sendError(ERRORPacket::Errors::NOT_LOGGED_IN, L"");
            return false;
        }
    }

    return true;
}

void BidiMessagingProtocolImpl::handleDirqPacket() {

    std::vector<File *> files = file->listFiles();

    std::wstring filesList = L"";
    for (auto f : files) {
        filesList += f->getName() + L'\0';
    }

    DATAPacket tempVar(connectionId.value(), static_cast<short>(filesList.length()), filesList.getBytes());
    connections->send(connectionId, &tempVar);
}

void BidiMessagingProtocolImpl::handleDelReqPacket(DELRQPacket *message) {
    File *file = new File(message->getFilename());
    try {
        if (file->delete ())
        {
            ACKPacket tempVar(ACK_OK);
            connections->send(connectionId, &tempVar);
            broadcastMessageToLogons(static_cast<char>(0), message->getFilename());
        }
        else
        {
            sendError(ERRORPacket::Errors::FILE_NOT_FOUND, L"");
        }
    }
    catch (const SecurityException &e) {
        sendError(ERRORPacket::Errors::ACCESS_VIOLATION, L"");
    }
}

void BidiMessagingProtocolImpl::broadcastMessageToLogons(char delOrIns, const std::wstring &filename) {
    for (* : :optional < int > conId : logOns)
    {
        BCASTPacket tempVar(delOrIns, filename);
        connections->send(conId, &tempVar);
    }
}

void BidiMessagingProtocolImpl::sendError(ERRORPacket::Errors *errorCode, const std::wstring &extraMsg) {
    ERRORPacket tempVar(static_cast<short>(errorCode->ordinal()), errorCode->getErrorMsg() + extraMsg);
    connections->send(connectionId, &tempVar);
}

void BidiMessagingProtocolImpl::handleLoginPacket(LOGRQPacket *message) {
    std::wstring userName = message->getUserName();

    if (std::find(logOns.begin(), logOns.end(), userName) != logOns.end()) {
        sendError(ERRORPacket::Errors::ALREADY_LOGGED_IN, L"");
    } else {
        logOns.push_back(connectionId);
        ACKPacket tempVar(ACK_OK);
        connections->send(connectionId, &tempVar);
    }
}

void BidiMessagingProtocolImpl::readFileIntoDataQueue(File *file) throw(IOException) {
    short blockPacket = 1;
    FileInputStream *fileInputStream = new FileInputStream(file);
    std::vector<char> dataBytes(512);
    short packetSize = static_cast<short>(fileInputStream->read(dataBytes));
    while (packetSize == 512) {
        DATAPacket *dataToSend = new DATAPacket(packetSize, blockPacket, dataBytes);
        dataQueue->add(dataToSend);
        blockPacket++;
        packetSize = static_cast<short>(fileInputStream->read(dataBytes));
    }
    if (packetSize == -1) {
        std::vector<char> lastDataBytes(0);
        DATAPacket *dataToSend = new DATAPacket(static_cast<short>(0), blockPacket, lastDataBytes);
        dataQueue->add(dataToSend);
    } else {
        dataBytes = Arrays::copyOf(dataBytes, packetSize);
        DATAPacket *dataToSend = new DATAPacket(packetSize, blockPacket, dataBytes);
        dataQueue->add(dataToSend);
    }
}

bool BidiMessagingProtocolImpl::shouldTerminate() {
    return shouldTerminate_Renamed;
}
