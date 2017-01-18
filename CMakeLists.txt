cmake_minimum_required(VERSION 2.8.4)
project(Client)

message(STATUS "start running cmake...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Weffc++ -std=c++11")

set(Boost_INCLUDE_DIR "C:/Program Files/boost_1_63_0/include/boost-1_63/")
set(Boost_LIBRARY_DIR "C:/Program Files/boost_1_63_0/lib/")

set(BOOST_ROOT "C:/Program Files/boost_1_63_0/")

#find_package(Boost COMPONENTS REQUIRED)

if(Boost_FOUND)

    LINK_DIRECTORIES(${Boost_LIBRARY_DIR})

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
   message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Client
#        src/connectionHandler.cpp src/echoClient.cpp include/connectionHandler.h
        packet/Packet.h packet/Packet.cpp
        packet/LOGRQPacket.h packet/LOGRQPacket.cpp
        packet/RRQPacket.h packet/RRQPacket.cpp
        packet/ACKPacket.h packet/ACKPacket.cpp
        packet/BCASTPacket.h packet/BCASTPacket.cpp
        packet/WRQPacket.h packet/WRQPacket.cpp
        packet/ERRORPacket.h packet/ERRORPacket.cpp
        packet/DATAPacket.h packet/DATAPacket.cpp
        packet/DELRQPacket.h packet/DELRQPacket.cpp
        packet/DIRQPacket.h packet/DIRQPacket.cpp
        packet/DISCPacket.h packet/DISCPacket.cpp
        src/EncdecTest.cpp include/EncdecTest.h
        src/MessageEncoderDecoder.cpp include/MessageEncoderDecoder.h
        src/ListenToServer.cpp src/ListenToServer.h
        src/EncdecTest.cpp include/EncdecTest.h
        src/ListenToKeyboard.cpp src/ListenToKeyboard.h
        src/Protocol.cpp src/Protocol.h)

if(Boost_FOUND)

target_link_libraries(Client ${Boost_LIBRARIES})

endif()