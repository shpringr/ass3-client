#pragma once

#include <vector>

namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace api
			{


				template<typename T>
				class MessageEncoderDecoder
				{

					/// <summary>
					/// add the next byte to the decoding process
					/// </summary>
					/// <param name="nextByte"> the next byte to consider for the currently decoded
					/// message </param>
					/// <returns> a message if this byte completes one or null if it doesnt. </returns>
				public:
					virtual T decodeNextByte(char nextByte) = 0;

					/// <summary>
					/// encodes the given message to bytes array
					/// </summary>
					/// <param name="message"> the message to encode </param>
					/// <returns> the encoded bytes </returns>
					virtual std::vector<char> encode(T message) = 0;

				};

			}
		}
	}
}
