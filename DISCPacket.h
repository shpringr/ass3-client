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


					class DISCPacket : public Packet
					{

					public:
						DISCPacket();


						virtual std::vector<char> toByteArr() override;
					};

				}
			}
		}
	}
}
