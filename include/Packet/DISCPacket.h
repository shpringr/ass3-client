#pragma once
#include "Packet.h"
#include <vector>
    class DISCPacket : public Packet {

    public:
        DISCPacket();


        DISCPacket(const DISCPacket &discPacket);
        DISCPacket& operator=(const DISCPacket &b);

        virtual char* toByteArr() override ;

        virtual ~DISCPacket();
    };


