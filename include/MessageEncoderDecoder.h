#pragma once

#include "MessageEncoderDecoder.h"
#include "../packet/Packet.h"
#include <string>
#include <vector>


/// <summary>
/// Created by ROTEM on 09/01/2017.
/// </summary>
class MessageEncoderDecoder<Packet *> {

private:
//    ByteBuffer *const opLengthBuffer = ByteBuffer::allocate(2);
//    ByteBuffer *lengthBuffer;
//    ByteBuffer *blockBuffer;
//    ByteBuffer *packetSizeBuffer;
//
//    ByteBuffer *errorBuffer;
    short errorCode = 0;
    std::vector<char> errorArr;

    short opCode = 0;

    std::vector<char> packetSizeArr;
    short packetSize = 0;
    std::vector<char> blockArr;
    short block = 0;
    char deletedAdd = 0;

    Packet *res;

public:
    virtual ~MessageEncoderDecoder() {
//        delete opLengthBuffer;
//        delete lengthBuffer;
//        delete blockBuffer;
//        delete packetSizeBuffer;
//        delete errorBuffer;
        delete res;
    }

    MessageEncoderDecoder();

private:
    void initAll();

    void initOpObjects();

public:
    virtual Packet *decodeNextByte(char nextByte);

private:
    void makeBCastPacket(char nextByte) ;

    void makeDelRqPacket(char nextByte) ;

    void makeLoginPacket(char nextByte) ;

    //std::vector<char> getDataFromBuffer(ByteBuffer *buffer);

    void makeDIRQPacket();

    void makeErrorPacket(char nextByte) ;

    void makeACKPacket(char nextByte);

    void makeDataPacket(char nextByte);

    void makeWRQPacket(char nextByte) ;

    void makeRRQPacket(char nextByte) ;

    void initOpCodeAndBuffers(char nextByte);

    //@TODO SHITTTTTTTTTTTTTTTTTTTTTTTTTTTT
public:
    virtual std::vector<char> encode(Packet *message);

    short MessageEncoderDecoder::bytesToShort(char bytesArr[]);
    void MessageEncoderDecoder::shortToBytes(short num, char bytesArr[]);

};