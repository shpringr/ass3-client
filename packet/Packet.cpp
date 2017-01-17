#include "Packet.h"

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

					short Packet::getOpCode()
					{
						return opCode;
					}

					std::vector<char> Packet::shortToBytes(short num)
					{
						std::vector<char> bytesArr(2);
						bytesArr[0] = static_cast<char>((num >> 8) & 0xFF);
						bytesArr[1] = static_cast<char>(num & 0xFF);
						return bytesArr;
					}
				}
			}
		}
	}
}
