cmake_minimum_required(VERSION 2.8.4)
project(Client)

message(STATUS "start running cmake...")
set(Boost_INCLUDE_DIR "C:/Program Files/boost_1_63_0/include/boost-1_63/")
set(Boost_LIBRARY_DIR "C:/Program Files/boost_1_63_0/lib/")

#find_package(Boost COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
   message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Client src/connectionHandler.cpp src/echoClient.cpp include/connectionHandler.h)

if(Boost_FOUND)

target_link_libraries(Client ${Boost_LIBRARIES})

endif()