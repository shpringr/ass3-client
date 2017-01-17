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


					class DIRQPacket : public Packet
					{

					public:
						DIRQPacket();


						virtual std::vector<char> toByteArr() override;
					};

				}
			}
		}
	}
}
