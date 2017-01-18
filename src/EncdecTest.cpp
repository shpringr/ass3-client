//
// Created by alonam on 1/15/17.
//
#include <cstring>
#include "../include/EncdecTest.h"
#include "../packet/WRQPacket.h"
#include "../packet/DATAPacket.h"
#include "../packet/DISCPacket.h"
#include "../packet/BCASTPacket.h"
#include "../packet/DELRQPacket.h"
#include "../packet/LOGRQPacket.h"
#include "../packet/DIRQPacket.h"
#include "../packet/ERRORPacket.h"
#include "../packet/RRQPacket.h"
#include "../packet/ACKPacket.h"


int maian(int argc, char *argv[]) {



    /* * * * * * * * * * * * * * * * * * * * * * * * * * *
                   TESTING THE ENCODER DECODER
                   /* * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // Instructions: 1. Change the names I used for your names.
    //               2. Import the thing you need
    //               3. Remove the "//" from the packet you want to test, and run it.
    //                  You can activate decode and then encode in order to see that you receive the same output as you started.
    //               *. Some of the tests are not relevant - You need to encode just: data, ack, bcast, and error.
    MessageEncoderDecoder encdec;
    EncdecTest test;
//  test.testRRQDecode(encdec); // 1 --works
//  test.testWRQDecode(encdec); // 2 --works
 // test.testDataDecode(encdec); // 3 --works
//  test.testDataEncode(encdec); // 3 --works
// test.testACKDecode(encdec); // 4 --works
 	// test.testACKEncode(encdec); // 4 --works
//  test.testErrorDecode(encdec); // 5 --works
//	test.testErrorEncode(encdec); // 5 --works
 	//test.testDIRQDecode(encdec); // 6 --works
 //	test.testLOGRQDecode(encdec); // 7 -- works
// 	test.testDELRQDecode(encdec); // 8 -- works
// 	test.testBCastDecode(encdec); // 9 --works
//  test.testBCastEncode(encdec); // 9 --works
//	test.testDISCDecode(encdec); // 10 --works
}


char *EncdecTest::vecToArr(vector<char> &v) {
    // Get a char pointer to the data in the vector
    char *buf = &v[0]; // For example , vec[1011,.... , 9101], so buf -> 1011 (Later, i'll send it with the size, so it will know when to finish)
    buf[v.size()] = '\0';
    return buf;
}


vector<char> EncdecTest::arrToVec(char *c) {
    int size = sizeof(c);
    vector<char> v(c, c + size);
    return v;
}

void EncdecTest::testDataDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 3, 0, 5, 1, 5, 1, 2, 3, 4, 5}; // 0,5 is the packetSize(5), 1,5 is the blockNum(261)
    // bytesToShort({0,5})=(short)5, bytesToShort({1,5})=(short)261
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    cout << "FLAG DataDecode 1" << endl;
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    cout << "FLAG DataDecode 2" << endl;
    DATAPacket *res1 = dynamic_cast<DATAPacket *>(res);
    cout << "FLAG DataDecode 3" << endl;
    short opcode = res1->getOpCode();
    short packetSize = res1->getPacketSize();
    short blockNum = res1->getBlock();
    char *dataBytes = res1->getData();
    cout << "FLAG DataDecode 4" << endl;
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " The packetSize is " << packetSize << "  and the blockNum is " << blockNum
         << endl;
    cout << "The data is " << endl;
    printArr(dataBytes);
}

void EncdecTest::testDataEncode(MessageEncoderDecoder &encdec) {
    vector<char> b = {1, 2, 3, 4, 5};
    DATAPacket *packet = new DATAPacket(((short) 5), ((short) 261), vecToArr(b));
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " is the Opcode " << packet->getPacketSize()
         << " is the packetSize " << packet->getBlock() << " is the Block Num " << endl;
    cout << "The data arr is " << endl;
    printArr(vecToArr(b));
    cout << "Output: " << endl;

    printArr(res); // Should be {0,3,0,5,1,5,1,2,3,4,5}
    cout << "The output should be {0,3,0,5,1,5,1,2,3,4,5}" << endl;
}


void EncdecTest::testDISCDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 10};
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    DISCPacket *res1 = dynamic_cast<DISCPacket *>(res);
    short opcode = res1->getOpCode();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << endl;
}

void EncdecTest::testDISCEncode(MessageEncoderDecoder &encdec) {
    DISCPacket *packet = new DISCPacket();
    char* res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " is the Opcode" << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,10}
    cout << "The output should be {0,10}" << endl;
}

void EncdecTest::testBCastDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 9, 1, 66, 67, 97, 115, 116, 83, 116, 114, 0};
    // popString({66,67,97,115,116,83,116,114})=(String)"BCastStr"
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    BCASTPacket *res1 = dynamic_cast<BCASTPacket *>(res);
    short opcode = res1->getOpCode();
    short deleted_or_added = res1->getDeletedAdd();
    string Filename = res1->getFileName();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " the deleted_or_added is " << deleted_or_added << "  and the Filename is "
         << Filename << endl;
}

void EncdecTest::testBCastEncode(MessageEncoderDecoder &encdec) {
    BCASTPacket *packet = new BCASTPacket ((char) 1, "BCastStr");
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " is the Opcode " << packet->getDeletedAdd()
         << " is the deleted_or_added code " << packet->getFileName() << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,9,1,66,67,97,115,116,83,116,114,0}
    cout << "The output should be {0,9,1,66,67,97,115,116,83,116,114,0}" << endl;
}

void EncdecTest::testDELRQDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 8, 68, 97, 110, 97, 0};
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    DELRQPacket *res1 = dynamic_cast<DELRQPacket *>(res);
    short opcode = res1->getOpCode();
    string fileName = res1->getFilename();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " and the fileName is " << fileName << endl;
}

void EncdecTest::testDELRQEncode(MessageEncoderDecoder &encdec) {
    DELRQPacket *packet = new DELRQPacket("Dana");
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " Opcode " << packet->getFilename() << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,8,68,97,110,97,0}
    cout << "The output should be {0,8,68,97,110,97,0}" << endl;
}


void EncdecTest::testLOGRQDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 7, 68, 97, 110, 97, 0};
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    LOGRQPacket *res1 = dynamic_cast<LOGRQPacket *>(res);
    short opcode = res1->getOpCode();
    string userName = res1->getUserName();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " and the userName is " << userName << endl;
}

void EncdecTest::testLOGRQEncode(MessageEncoderDecoder &encdec) {
    LOGRQPacket *packet = new LOGRQPacket("Dana");
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " Opcode " << packet->getUserName() << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,7,68,97,110,97,0}
    cout << "The output should be {0,7,68,97,110,97,0}" << endl;
}


void EncdecTest::testDIRQDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 6};
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    DIRQPacket *res1 = dynamic_cast<DIRQPacket *>(res);
    short opcode = res1->getOpCode();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << endl;
}

void EncdecTest::testDIRQEncode(MessageEncoderDecoder &encdec) {
    DIRQPacket *packet = new DIRQPacket();
    char* res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " is the Opcode" << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,6}
    cout << "The output should be {0,6}" << endl;
}


void EncdecTest::testErrorDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 5, 14, 20, 69, 114, 114, 111, 114, 32, 75, 97, 112, 97, 114, 97, 0};
    // bytesToShort({14,20})=(short)3604, and popString({69,114,114,111,114,32,75,97,112,97,114,97})=(String)"Error Kapara"
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    ERRORPacket *res1 = dynamic_cast<ERRORPacket *>(res);
    short opcode = res1->getOpCode();
    short errorCode = res1->getErrorCode();
    string errorMsg = res1->getErrMsg();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " The Error code is " << errorCode << "  and the error messege is "
         << errorMsg << endl;
}

void EncdecTest::testErrorEncode(MessageEncoderDecoder &encdec) {
    cout << "I'm at the Error encode" << endl;
    ERRORPacket *packet = new ERRORPacket((short) 3604, "Error Kapara");
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " is the Opcode " << packet->getErrorCode()
         << " is the error code " << packet->getErrMsg() << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,5,14,20 ,69,114 ,114,111,114,32,75,97,112,97,114,97 ,0}
    cout << "The output should be {0,5,14,20,69,114,114,111,114,32,75,97,112,97,114,97,0}" << endl;
}

void EncdecTest::testRRQDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 1, 68, 97, 110, 97, 0};
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    RRQPacket *res1 = dynamic_cast<RRQPacket *>(res);
    short opcode = res1->getOpCode();
    string fileName = res1->getFileName();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " and the fileName is " << fileName << endl;
}


void EncdecTest::testRRQEncode(MessageEncoderDecoder &encdec) {
    RRQPacket *packet = new RRQPacket("Dana");
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " Opcode " << packet->getFileName() << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,1,68,97,110,97,0}
    cout << "The output should be {0,1,68,97,110,97,0}" << endl;
}

void EncdecTest::testWRQDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 2, 68, 97, 110, 97, 0};
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    WRQPacket *res1 = dynamic_cast<WRQPacket *>(res);
    short opcode = res1->getOpCode();
    string fileName = res1->getFileName();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " and the fileName is " << fileName << endl;
}

void EncdecTest::testWRQEncode(MessageEncoderDecoder &encdec) {
    WRQPacket *packet = new WRQPacket("Dana");
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " Opcode " << packet->getFileName() << endl;
    cout << "Output: " << endl;

    printArr(res); // Should be {0,2,68,97,110,97,0}
    cout << "The output should be {0,2,68,97,110,97,0}" << endl;
}

void EncdecTest::testACKDecode(MessageEncoderDecoder &encdec) {
    vector<char> b = {0, 4, 14, 20}; // bytesToShort({14,20})=(short)3604
    Packet *res = nullptr;
    cout << "Before decoding, the Arr is" << endl;
    printArr(vecToArr(b));
    for (unsigned int i = 0; i < b.size(); i++)
        res = encdec.decodeNextByte(b[i]);
    ACKPacket *res1 = dynamic_cast<ACKPacket *>(res);
    short opcode = res1->getOpCode();
    short blockNum = res1->getBlock();
    cout << "After decoding the arr, we've got a packet!" << endl;
    cout << "The opcode is " << opcode << " and the blockNum is " << blockNum << endl;
}

void EncdecTest::testACKEncode(MessageEncoderDecoder &encdec) {
    ACKPacket* packet = new ACKPacket(((short) 3604)); // bytesToShort({14,20})=(short)3604
    char *res = encdec.encode(packet);
    cout << "Encoding the packet " << packet->getOpCode() << " Opcode " << packet->getBlock() << endl;
    cout << "Output: " << endl;
    cout << string(res);
    //printArr(res); // Should be {0,2,68,97,110,97,0}
    cout << "The output should be {0,4,14,20}" << endl;
}


void EncdecTest::printArr(char b[])
{
    string s;
    for (unsigned int i = 0; i < sizeof(b); i++) {
        s = b[i] + " ";
    }
    //{0,3,0,5,1,5,1,2,3,4,5}
    cout << s << endl;
}

short EncdecTest::bytesToShort(vector<char> byteArr) {
    short result = (short) ((byteArr[0] & 0xff) << 8);
    result += (short) (byteArr[1] & 0xff);
    return result;
}

vector<char> EncdecTest::shortToBytes(short num) {
    vector<char> bytesArr;
    bytesArr.push_back(((num >> 8) & 0xFF));
    bytesArr.push_back((num & 0xFF));
    return bytesArr;

}

vector<char> EncdecTest::popTwoFirstBytes(vector<char> dataToDecode) {
    dataToDecode.erase(dataToDecode.begin());
    dataToDecode.erase(dataToDecode.begin());
    return dataToDecode;
}


string EncdecTest::popString(vector<char> bytes) {

    std::string s(bytes.begin(), bytes.end());
    return s;
    //notice that we explicitly requesting that the string will be decoded from UTF-8
    //this is not actually required as it is the default encoding in java.

}

