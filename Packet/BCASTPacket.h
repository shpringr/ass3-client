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


					class BCASTPacket : public Packet
					{
					public:
						char deletedAdd = 0;
						std::wstring fileName;

						BCASTPacket(char deletedAdd, const std::wstring &fileName);

						virtual char getDeletedAdd();

						virtual std::wstring getFileName();

						virtual std::vector<char> toByteArr() override;
					};

				}
			}
		}
	}
}
