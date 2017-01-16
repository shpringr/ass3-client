#pragma once

#include "BidiMessagingProtocol.h"
#include <string>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace bgu { namespace spl171 { namespace net { namespace api { namespace bidi { template<typename T>class Connections; } } } } }

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

					using namespace bgu::spl171::net::impl::packet;


//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//					import static bgu.spl171.net.impl.packet.ERRORPacket.Errors.*;


					class BidiMessagingProtocolImpl : public BidiMessagingProtocol<Packet*>
					{

					private:
						static constexpr short ACK_OK = 0;
						static std::vector<int> logOns;
						static File *const file = new File(L"Server/Files");

//JAVA TO C++ CONVERTER NOTE: Fields cannot have the same name as methods:
						bool shouldTerminate_Renamed = false;
						Connections *connections;
						boost::optional<int> connectionId;
						bool isFirstCommand = true;
						LinkedBlockingQueue<DATAPacket*> *dataQueue = new LinkedBlockingQueue<DATAPacket*>();
						std::wstring state = L"";
						File *fileToWrite = nullptr;

					public:
						virtual ~BidiMessagingProtocolImpl()
						{
							delete connections;
							delete dataQueue;
							delete fileToWrite;
						}

						virtual void start(int connectionId, Connections *connections) override;

						virtual void process(Packet *message) override;

					private:
						void handleDiscPacket();

						void handleBCastPacket();

						//TODO: can we get errors from client to server?
						void handleErrorPacket();

						void handleAckPacket(ACKPacket *message);

						void handleDataPacket(DATAPacket *message);

						void handleWritePacket(WRQPacket *message);

						void handleReadPacket(RRQPacket *message);
						bool isLegalFirstCommand(Packet *message);

						//TODO: make sure it doesnt return file that are uploading.
						//TODO: what happens if the list is more than 512b?
						void handleDirqPacket();

						void handleDelReqPacket(DELRQPacket *message);

						void broadcastMessageToLogons(char delOrIns, const std::wstring &filename);

						void sendError(ERRORPacket::Errors *errorCode, const std::wstring &extraMsg);

						void handleLoginPacket(LOGRQPacket *message);

						void readFileIntoDataQueue(File *file) throw(IOException);

					public:
						virtual bool shouldTerminate() override;
					};
				}
			}
		}
	}
}
