#pragma once

#include "Packet.h"
#include <vector>

namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace impl
			{
				namespace packet
				{


					class DATAPacket : public Packet
					{
					public:
						short packetSize = 0;
						short block = 0;
						std::vector<char> data;

						DATAPacket(short packetSize, short block, std::vector<char> &data);

						virtual short getPacketSize();

						virtual short getBlock();

						virtual std::vector<char> getData();

						virtual std::vector<char> toByteArr() override;
					};

				}
			}
		}
	}
}
