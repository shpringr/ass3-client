#include "../include/MessageEncoderDecoderImpl.h"

namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace api
			{
				using namespace bgu::spl171::net::impl::packet;

				MessageEncoderDecoderImpl::MessageEncoderDecoderImpl()
				{
					initAll();
				}

				void MessageEncoderDecoderImpl::initAll()
				{
					initOpObjects();
					if (lengthBuffer != nullptr)
					{
						lengthBuffer->clear();
					}
					if (blockBuffer != nullptr)
					{
						blockBuffer->clear();
					}
					if (packetSizeBuffer != nullptr)
					{
						packetSizeBuffer->clear();
					}
					if (errorBuffer != nullptr)
					{
						errorBuffer->clear();
					}
					errorCode = -1;
					errorArr.clear();
					packetSizeArr.clear();
					packetSize = 0;
					blockArr.clear();
					block = 0;
					deletedAdd = L'e';
				}

				void MessageEncoderDecoderImpl::initOpObjects()
				{
					if (opLengthBuffer != nullptr)
					{
						opLengthBuffer->clear();
					}
					opCode = 0;
				}

				Packet *MessageEncoderDecoderImpl::decodeNextByte(char nextByte) throw(UnsupportedEncodingException)
				{
					switch (opCode)
					{
						case 0:
							initOpCodeAndBuffers(nextByte);
							break;

						case 1:
							makeRRQPacket(nextByte);
							break;

						case 2:
							makeWRQPacket(nextByte);
							break;

						case 3:
							makeDataPacket(nextByte);
							break;

						case 4:
							makeACKPacket(nextByte);
							break;

						case 5:
							makeErrorPacket(nextByte);
							break;

						case 6:
							break;

						case 7:
							makeLoginPacket(nextByte);
							break;

						case 8:
							makeDelRqPacket(nextByte);
							break;

						case 9:
							makeBCastPacket(nextByte);
							break;

						case 10:
							break;

					}

					return res;
				}

				void MessageEncoderDecoderImpl::makeBCastPacket(char nextByte) throw(UnsupportedEncodingException)
				{
					if (deletedAdd == L'e')
					{
						deletedAdd = nextByte;
					}
					else
					{
						if (nextByte != L'\0')
						{
							lengthBuffer->put(nextByte);
						}
						else
						{ //nextByte == '\0'
							std::wstring fileName = std::wstring(getDataFromBuffer(lengthBuffer), L"UTF-8");
							res = new BCASTPacket(deletedAdd, fileName);
							initAll();
						}
					}
				}

				void MessageEncoderDecoderImpl::makeDelRqPacket(char nextByte) throw(UnsupportedEncodingException)
				{
					if (nextByte != L'\0')
					{
						lengthBuffer->put(nextByte);
					}
					else
					{ //nextByte == '\0'
						std::wstring fileName = std::wstring(getDataFromBuffer(lengthBuffer), L"UTF-8");
						res = new DELRQPacket(fileName);
						initAll();
					}
				}

				void MessageEncoderDecoderImpl::makeLoginPacket(char nextByte) throw(UnsupportedEncodingException)
				{
					if (nextByte != L'\0')
					{
						lengthBuffer->put(nextByte);
					}
					else
					{ //nextByte == '\0'
						std::wstring userName = std::wstring(getDataFromBuffer(lengthBuffer), L"UTF-8");
						res = new LOGRQPacket(userName);
						initAll();
					}
				}

				std::vector<char> MessageEncoderDecoderImpl::getDataFromBuffer(ByteBuffer *buffer)
				{
					buffer->flip();
					std::vector<char> objectBytes(buffer->limit());
					buffer->get(objectBytes,0, buffer->limit());
					return objectBytes;
				}

				void MessageEncoderDecoderImpl::makeDIRQPacket()
				{
					res = new DIRQPacket();
					initAll();
				}

				void MessageEncoderDecoderImpl::makeErrorPacket(char nextByte) throw(UnsupportedEncodingException)
				{
					if (errorArr.empty())
					{
						errorBuffer->put(nextByte);
						if (!errorBuffer->hasRemaining())
						{
							errorArr = getDataFromBuffer(errorBuffer);
							errorCode = bytesToShort(errorArr);
						}
					}
					else
					{
						if (nextByte != L'\0')
						{
							lengthBuffer->put(nextByte);
						}
						else
						{ //nextByte == '\0'
							std::wstring errMsg = std::wstring(getDataFromBuffer(lengthBuffer), L"UTF-8");
							res = new ERRORPacket(errorCode, errMsg);
							initAll();
						}
					}
				}

				void MessageEncoderDecoderImpl::makeACKPacket(char nextByte)
				{
					lengthBuffer->put(nextByte);
					if (!lengthBuffer->hasRemaining())
					{
						short blockAck = bytesToShort(getDataFromBuffer(lengthBuffer));
						res = new ACKPacket(blockAck);
						initAll();
					}
				}

				void MessageEncoderDecoderImpl::makeDataPacket(char nextByte)
				{
					if (packetSizeArr.empty())
					{
						packetSizeBuffer->put(nextByte);
						if (!packetSizeBuffer->hasRemaining())
						{
							packetSizeArr = getDataFromBuffer(packetSizeBuffer);
							packetSize = bytesToShort(packetSizeArr);
						}
					}
					else if (blockArr.empty())
					{
						blockBuffer->put(nextByte);
						if (!blockBuffer->hasRemaining())
						{
							blockArr = getDataFromBuffer(blockBuffer);
							block = bytesToShort(blockArr);
						}
					}
					else
					{
						lengthBuffer->put(nextByte);
						packetSize--;
						if (packetSize == 0)
						{
							std::vector<char> bytes = getDataFromBuffer(lengthBuffer);
							res = new DATAPacket(static_cast<short>(bytes.size()), block, bytes);
							initAll();
						}
					}
				}

				void MessageEncoderDecoderImpl::makeWRQPacket(char nextByte) throw(UnsupportedEncodingException)
				{
					if (nextByte != L'\0')
					{
						lengthBuffer->put(nextByte);
					}
					else
					{ //nextByte == '\0'
						std::wstring filename = std::wstring(getDataFromBuffer(lengthBuffer), L"UTF-8");
						res = new WRQPacket(filename);
						initAll();
					}
				}

				void MessageEncoderDecoderImpl::makeRRQPacket(char nextByte) throw(UnsupportedEncodingException)
				{
					if (nextByte != L'\0')
					{
						lengthBuffer->put(nextByte);
					}
					else
					{ //nextByte == '\0'
						std::wstring filename = std::wstring(getDataFromBuffer(lengthBuffer), L"UTF-8");
						res = new RRQPacket(filename);
						initAll();
					}
				}

				void MessageEncoderDecoderImpl::initOpCodeAndBuffers(char nextByte)
				{
					opLengthBuffer->put(nextByte);
					if (!opLengthBuffer->hasRemaining())
					{
						opCode = bytesToShort(getDataFromBuffer(opLengthBuffer));
						switch (opCode)
						{
							case 1 :
						case 2 :
					case 7:
				case 8:
								case 9:
				lengthBuffer = ByteBuffer::allocate(516);
								break;
							case 3:
								packetSizeBuffer = ByteBuffer::allocate(2);
								blockBuffer = ByteBuffer::allocate(2);
								lengthBuffer = ByteBuffer::allocate(512);
								break;
							case 4:
								lengthBuffer = ByteBuffer::allocate(2);
								break;
							case 5:
								errorBuffer = ByteBuffer::allocate(2);
								lengthBuffer = ByteBuffer::allocate(516);
								break;
							case 6:
								res = new DIRQPacket();
								initOpObjects();
								break;

							case 10:
								res = new DISCPacket();
								initOpObjects();
								break;
						}
					}
				}

				std::vector<char> MessageEncoderDecoderImpl::encode(Packet *message)
				{
					return message->toByteArr();
				}

				short MessageEncoderDecoderImpl::bytesToShort(std::vector<char> &byteArr)
				{
					short result = static_cast<short>((byteArr[0] & 0xff) << 8);
					result += static_cast<short>(byteArr[1] & 0xff);
					return result;
				}

				std::vector<char> MessageEncoderDecoderImpl::shortToBytes(short num)
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
