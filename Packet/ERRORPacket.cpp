#include "ERRORPacket.h"
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

					ERRORPacket::ERRORPacket(short errorCode, const std::wstring &errMsg)
					{
						this->errorCode = errorCode;
						this->errMsg = errMsg;
						Packet::opCode = 5;
					}

					short ERRORPacket::getErrorCode()
					{
						return errorCode;
					}

					std::wstring ERRORPacket::getErrMsg()
					{
						return errMsg;
					}

					std::vector<char> ERRORPacket::toByteArr()
					{
						ByteBuffer *lengthBuffer = ByteBuffer::allocate(2 + 2 + getErrMsg().length() + 1);
						lengthBuffer->put(shortToBytes(opCode));
						lengthBuffer->put(shortToBytes(errorCode));
						try
						{
							lengthBuffer->put(errMsg.getBytes(L"UTF-8"));
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
