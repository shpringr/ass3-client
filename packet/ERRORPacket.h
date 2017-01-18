#pragma once

#include "Packet.h"
#include <vector>
using namespace std;
#include <string>
#include <iostream>

    class ERRORPacket : public Packet {

    public:
        short errorCode = 0;
        string errMsg;

    public:
//        enum class Errors {
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    NOT_DEFINED(L"Not defined, see error message (if any)"),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    FILE_NOT_FOUND(L"File not found – RRQ \\ DELRQ of non-existing file"),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    ACCESS_VIOLATION(L"Access violation – File cannot be written, read or deleted."),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    DISK_FULL(L"Disk full or allocation exceeded – No room in disk."),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    ILLEGAL_TFTP_OPERATION(L"Illegal TFTP operation – Unknown Opcode."),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    FILE_ALREADY_EXISTS(L"File already exists – File name exists on WRQ."),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    NOT_LOGGED_IN(L"User not logged in – Any opcode received before Login completes."),
////JAVA TO C++ CONVERTER TODO TASK: Enum values cannot be strings in C++:
//                    ALREADY_LOGGED_IN(L"User already logged in – Login username already connected.");
//
////JAVA TO C++ CONVERTER TODO TASK: Enums cannot contain fields in C++:
////							private String errorMsg;
//
////JAVA TO C++ CONVERTER TODO TASK: Enums cannot contain methods in C++:
////							Errors(String msg)
//            //		{
//            //			errorMsg = msg;
//            //		}
//
////JAVA TO C++ CONVERTER TODO TASK: Enums cannot contain methods in C++:
////							public String getErrorMsg()
//            //		{
//            //			return errorMsg;
//            //		}
//        };

    public:
        ERRORPacket(short errorCode, const string &errMsg);

        virtual short getErrorCode();

        virtual string getErrMsg();

    virtual void toByteArr(char *outChar) override ;
    };



