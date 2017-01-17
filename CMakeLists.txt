#cmake_minimum_required(VERSION 3.6)
#project(Client)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Weffc++ -std=c++11")
#
#set(SOURCE_FILES Boost_Echo_Client)
#add_executable(Client ${SOURCE_FILES})

#My cmake doesn't contain anything, it just works I don't know why:
cmake_minimum_required(VERSION 3.6)
project(Client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/connectionHandler.cpp src/echoClient.cpp include/connectionHandler.h)
add_executable(Client ${SOURCE_FILES})
set(Boost_INCLUDE_DIR "C:/boost_1_63_0/include/boost-1_63/boost")
set(Boost_LIBRARY_DIR "C:/boost_1_63_0/lib")
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries( Client ${Boost_LIBRARY_DIR} )
