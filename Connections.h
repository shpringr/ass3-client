#pragma once

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


					template<typename T>
					class Connections
					{

					public:
						virtual bool send(int connectionId, T msg) = 0;

						virtual void broadcast(T msg) = 0;

						virtual void disconnect(int connectionId) = 0;
					};
				}
			}
		}
	}
}
