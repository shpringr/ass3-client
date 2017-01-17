#include "RRQPacket.h"

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

					RRQPacket::RRQPacket(const std::wstring &filename)
					{
						fileName = filename;
						Packet::opCode = 1;
					}

					std::wstring RRQPacket::getFileName()
					{
						return fileName;
					}

					std::vector<char> RRQPacket::toByteArr()
					{
						ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + fileName.length() + 1);
						lengthBuffer->put(shortToBytes(opCode));
						try
						{
							lengthBuffer->put(fileName.getBytes(L"UTF-8"));
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
						lengthBuffer->put(static_cast<char>(0));
						return lengthBuffer->array_Renamed();
					}
				}
			}
		}
	}
}
