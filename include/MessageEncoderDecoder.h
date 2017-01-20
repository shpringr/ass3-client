#pragma once

#include "MessageEncoderDecoder.h"
#include "Packet/Packet.h"
#include <string>
#include <vector>


/// <summary>
/// Created by ROTEM on 09/01/2017.
/// </summary>
class MessageEncoderDecoder{

private:

    short opCode = 0;
    Packet* res = nullptr;

    char* lengthArr;
    short lengthArrSize=0;
    short lengthArrIndex=0;

    char* errorArr;
    short errorArrSize=0;
    short errorArrIndex=0;

    short errorCode = -1;

    char* packetArr;
    short packetArrSize=0;
    short packetArrIndex=0;

    short packetSize=0;

    char* blockArr;
    short blockArrSize=0;
    short blockArrIndex=0;

    short block=0;

    char deletedAdd = 0;

public:

    MessageEncoderDecoder();
    ~MessageEncoderDecoder();

private:
    void initAll();

    void initOpObjects();

public:
    virtual Packet *decodeNextByte(char nextByte);

private:
    void makeBCastPacket(char nextByte) ;

    void makeDelRqPacket(char nextByte) ;

    void makeLoginPacket(char nextByte) ;

    void makeErrorPacket(char nextByte) ;

    void makeACKPacket(char nextByte);

    void makeDataPacket(char nextByte);

    void makeWRQPacket(char nextByte) ;

    void makeRRQPacket(char nextByte) ;

    void initOpCodeAndBuffers(char nextByte);

public:
    virtual char* encode(Packet *message);

    short bytesToShort(char bytesArr[]);
    void shortToBytes(short num, char bytesArr[]);

};