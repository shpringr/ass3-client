
#ifndef CLIENTDANA_ENCDECTEST_H
#define CLIENTDANA_ENCDECTEST_H
#include "../include/MessageEncoderDecoder.h"
using namespace std;
#include <string>
#include <iostream>


class EncdecTest {

public:
    MessageEncoderDecoder* encdec = new MessageEncoderDecoder();
     char* vecToArr(vector<char>& v);
     vector<char> arrToVec(char* c);
     void testDataDecode (MessageEncoderDecoder& encdec);
     void testDataEncode (MessageEncoderDecoder& encdec);
     void testDISCDecode (MessageEncoderDecoder& encdec);
     void testDISCEncode (MessageEncoderDecoder& encdec);
     void testBCastDecode (MessageEncoderDecoder& encdec);
     void testBCastEncode (MessageEncoderDecoder& encdec);
     void testDELRQDecode (MessageEncoderDecoder& encdec);
     void testDELRQEncode (MessageEncoderDecoder& encdec);
     void testLOGRQDecode (MessageEncoderDecoder& encdec);
     void testLOGRQEncode (MessageEncoderDecoder& encdec);
     void testDIRQDecode (MessageEncoderDecoder& encdec);
     void testDIRQEncode (MessageEncoderDecoder& encdec);
     void testErrorDecode (MessageEncoderDecoder& encdec);
     void testErrorEncode (MessageEncoderDecoder& encdec);
     void testRRQDecode (MessageEncoderDecoder& encdec);
     void testRRQEncode (MessageEncoderDecoder& encdec);
     void testWRQDecode (MessageEncoderDecoder& encdec);
     void testWRQEncode (MessageEncoderDecoder& encdec);
     void testACKDecode (MessageEncoderDecoder& encdec);
     void testACKEncode (MessageEncoderDecoder& encdec);
     void printArr(char b[]);
     short bytesToShort(vector<char> byteArr);
     vector<char> shortToBytes(short num);
     vector<char> popTwoFirstBytes(vector<char> dataToDecode);
     string popString(vector<char> bytes);

};


#endif //CLIENTDANA_ENCDECTEST_H