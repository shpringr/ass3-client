cmake_minimum_required(VERSION 2.8.4)
project(Client)

message(STATUS "start running cmake...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 ")

set(Boost_INCLUDE_DIR "C:/Boost/include/boost-1_63/")
set(Boost_LIBRARY_DIR "C:/Boost/lib/")

set(BOOST_ROOT "C:/Boost/")

find_package(Boost 1.63.0 COMPONENTS filesystem system thread REQUIRED)

#if(Boost_FOUND)

    LINK_DIRECTORIES(${Boost_LIBRARY_DIR})

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
   message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

#endif()

add_executable(Client
        src/connectionHandler.cpp include/connectionHandler.h
        include/Packet/Packet.h src/packet/Packet.cpp
        include/Packet/LOGRQPacket.h src/packet/LOGRQPacket.cpp
        include/Packet/RRQPacket.h src/packet/RRQPacket.cpp
        include/Packet/ACKPacket.h src/packet/ACKPacket.cpp
        include/Packet/BCASTPacket.h src/packet/BCASTPacket.cpp
        include/Packet/WRQPacket.h src/packet/WRQPacket.cpp
        include/Packet/ERRORPacket.h src/packet/ERRORPacket.cpp
        include/Packet/DATAPacket.h src/packet/DATAPacket.cpp
        include/Packet/DELRQPacket.h src/packet/DELRQPacket.cpp
        include/Packet/DIRQPacket.h src/packet/DIRQPacket.cpp
        include/Packet/DISCPacket.h src/packet/DISCPacket.cpp
        src/EncdecTest.cpp include/EncdecTest.h
        src/MessageEncoderDecoder.cpp include/MessageEncoderDecoder.h
        src/ListenToServer.cpp include/ListenToServer.h
        src/EncdecTest.cpp include/EncdecTest.h
        src/ListenToKeyboard.cpp include/ListenToKeyboard.h
        src/threads.cpp
        )

#if(Boost_FOUND)
    target_link_libraries(Client ${Boost_LIBRARIES} ws2_32)

#endif()