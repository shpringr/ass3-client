#pragma once

#include "MessageEncoderDecoder.h"
#include "Packet.h"
#include <string>
#include <vector>

namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace api
			{

				using namespace bgu::spl171::net::impl::packet;


				/// <summary>
				/// Created by ROTEM on 09/01/2017.
				/// </summary>
				class MessageEncoderDecoderImpl : public MessageEncoderDecoder<Packet*>
				{

				private:
					ByteBuffer *const opLengthBuffer = ByteBuffer::allocate(2);
					ByteBuffer *lengthBuffer;
					ByteBuffer *blockBuffer;
					ByteBuffer *packetSizeBuffer;

					ByteBuffer *errorBuffer;
					short errorCode = 0;
					std::vector<char> errorArr;

					short opCode = 0;

					std::vector<char> packetSizeArr;
					short packetSize = 0;
					std::vector<char> blockArr;
					short block = 0;
					char deletedAdd = 0;

					Packet *res;

				public:
					virtual ~MessageEncoderDecoderImpl()
					{
						delete opLengthBuffer;
						delete lengthBuffer;
						delete blockBuffer;
						delete packetSizeBuffer;
						delete errorBuffer;
						delete res;
					}

					MessageEncoderDecoderImpl();

				private:
					void initAll();

					void initOpObjects();

				public:
					virtual Packet *decodeNextByte(char nextByte) throw(UnsupportedEncodingException) override;

				private:
					void makeBCastPacket(char nextByte) throw(UnsupportedEncodingException);

					void makeDelRqPacket(char nextByte) throw(UnsupportedEncodingException);

					void makeLoginPacket(char nextByte) throw(UnsupportedEncodingException);

					std::vector<char> getDataFromBuffer(ByteBuffer *buffer);

					void makeDIRQPacket();

					void makeErrorPacket(char nextByte) throw(UnsupportedEncodingException);

					void makeACKPacket(char nextByte);

					void makeDataPacket(char nextByte);

					void makeWRQPacket(char nextByte) throw(UnsupportedEncodingException);

					void makeRRQPacket(char nextByte) throw(UnsupportedEncodingException);

					void initOpCodeAndBuffers(char nextByte);

					//@TODO SHITTTTTTTTTTTTTTTTTTTTTTTTTTTT
				public:
					virtual std::vector<char> encode(Packet *message);

					//Decode 2 bytes to short
					virtual short bytesToShort(std::vector<char> &byteArr);

					//Encode short to 2 bytes
					virtual std::vector<char> shortToBytes(short num);

				};
			}
		}
	}
}
