cmake_minimum_required(VERSION 3.6)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Weffc++ -std=c++11")

set(SOURCE_FILES BidiMessagingProtocol.h BidiMessagingProtocolImpl.h BidiMessagingProtocolImpl.cpp
        EncoderDecTest.cpp EncoderDecTest.h MessageEncoderDecoder.cpp MessageEncoderDecoder.h
        MessageEncoderDecoderImpl.cpp MessageEncoderDecoderImpl.h )
add_executable(Client ${SOURCE_FILES})
set(Boost_INCLUDE_DIR "C:/boost_1_63_0/include/boost-1_63/boost")
set(Boost_LIBRARY_DIR "C:/boost_1_63_0/lib")
find_package(Boost 1.63.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
TARGET_LINK_LIBRARIES( Client ${Boost_LIBRARY_DIR} )