cmake_minimum_required(VERSION 3.6)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Weffc++ -std=c++11")

set(SOURCE_FILES BidiMessagingProtocol.h BidiMessagingProtocolImpl.h BidiMessagingProtocolImpl.cpp
        EncoderDecTest.cpp EncoderDecTest.h MessageEncoderDecoder.cpp MessageEncoderDecoder.h
        MessageEncoderDecoderImpl.cpp MessageEncoderDecoderImpl.h )
add_executable(Client ${SOURCE_FILES})