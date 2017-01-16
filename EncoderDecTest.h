#pragma once

#include <string>
#include <vector>
#include <iostream>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace bgu { namespace spl171 { namespace net { namespace api { template<typename T>class MessageEncoderDecoder; } } } }

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
				/// Created by Ofir & Nitsan on 11/01/2017.
				/// </summary>
				class EncoderDecTest
				{

				private:
					static MessageEncoderDecoder<Packet*> *p;

					static void main(std::vector<std::wstring> &args);

					static void BCASTTest();

					static void ERRORtest();

					static std::vector<char> shortTObyte(short num);


				public:
					virtual std::vector<char> shortToBytes(short num);

				private:
					static void DATAtest();

					static void DIRQtest();

					static void ACKTest();

					static void DISCTest();

					static void RRQTest();

					static void WRQTest();

					static void DELRQtest();


					static void LOGRQtest();
				};
			}
		}
	}
}
