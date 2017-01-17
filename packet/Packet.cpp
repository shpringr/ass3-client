#include "Packet.h"

				namespace packet
				{
					short Packet::getOpCode()
					{
						return opCode;
					}

					short bytesToShort(char* bytesArr)
					{
						short result = (short)((bytesArr[0] & 0xff) << 8);
						result += (short)(bytesArr[1] & 0xff);
						return result;
					}

					void shortToBytes(short num, char* bytesArr)
					{
						bytesArr[0] = (char) ((num >> 8) & 0xFF);
						bytesArr[1] = (char) (num & 0xFF);
					}
				}