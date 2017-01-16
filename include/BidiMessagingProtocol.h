#pragma once

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace bgu { namespace spl171 { namespace net { namespace api { namespace bidi { template<typename T>class Connections; } } } } }

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace api
			{
				namespace bidi
				{

					/// 
					/// <summary>
					/// @author bennyl
					/// </summary>
					template<typename T>
					class BidiMessagingProtocol
					{

					public:
						virtual void start(int connectionId, Connections<T> *connections) = 0;

						virtual void process(T message) = 0;

						/// <returns> true if the connection should be terminated </returns>
						virtual bool shouldTerminate() = 0;
					};
				}
			}
		}
	}
}
