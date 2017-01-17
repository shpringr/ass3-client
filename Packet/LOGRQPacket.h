#pragma once

#include "Packet.h"
#include <string>
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


					class LOGRQPacket : public Packet
					{
					private:
						std::wstring userName;


					public:
						LOGRQPacket(const std::wstring &userName);

						virtual std::wstring getUserName();


						virtual std::vector<char> toByteArr() override;
					};

				}
			}
		}
	}
}
