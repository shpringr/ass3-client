#include "EncoderDecTest.h"
#include "MessageEncoderDecoder.h"

namespace bgu
{
	namespace spl171
	{
		namespace net
		{
			namespace api
			{
				using namespace bgu::spl171::net::impl::packet;
MessageEncoderDecoder<Packet*> *EncoderDecTest::p = new MessageEncoderDecoderImpl();

				void EncoderDecTest::main(std::vector<std::wstring> &args)
				{

					// log request test
					LOGRQtest();
					DELRQtest();
					WRQTest();
					RRQTest();
					DISCTest();
					ACKTest();
					BCASTTest();
					DIRQtest();
					DATAtest();
					ERRORtest();
				}

				void EncoderDecTest::BCASTTest()
				{
					Packet *tmp = nullptr;
					std::wstring filename = L"azov_oti_beshket";
					BCASTPacket *bcastPacket = new BCASTPacket(static_cast<char>(0), filename);
					std::vector<char> en = bcastPacket->toByteArr();
					for (int i = 0 ; i < en.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(en[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"BCASTPacket - ");
					if (dynamic_cast<BCASTPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<BCASTPacket*>(tmp))->getFileName().equals(filename) && (static_cast<BCASTPacket*>(tmp))->getDeletedAdd() == static_cast<char>(0) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}

				void EncoderDecTest::ERRORtest()
				{
					Packet *tmp = nullptr;
					std::wstring error = L"azov_oti_beshket";
					ERRORPacket *er = new ERRORPacket(static_cast<short>(4), error);
					std::vector<char> en = er->toByteArr();
					for (int i = 0 ; i < en.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(en[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"ERRORPacket - ");
					if (dynamic_cast<ERRORPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<ERRORPacket*>(tmp))->getErrMsg().equals(error) && (static_cast<ERRORPacket*>(tmp))->getErrorCode() == static_cast<short>(4) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}

				std::vector<char> EncoderDecTest::shortTObyte(short num)
				{
					std::vector<char> bytesArr(2);
					bytesArr[0] = static_cast<char>((num >> 8) & 0xFF);
					bytesArr[1] = static_cast<char>(num & 0xFF);
					return bytesArr;
				}

				std::vector<char> EncoderDecTest::shortToBytes(short num)
				{
					std::vector<char> bytesArr(2);
					bytesArr[0] = static_cast<char>((num >> 8) & 0xFF);
					bytesArr[1] = static_cast<char>(num & 0xFF);
					return bytesArr;
				}

				void EncoderDecTest::DATAtest()
				{
					Random *rnd = new Random((Date()).getTime());
					Packet *tmp = nullptr;
					std::vector<char> data(400);
					for (int i = 0; i < 400; i++)
					{
						data[i] = static_cast<char>(rnd->nextInt(255) + 1);
					}

					DATAPacket *dataPacket = new DATAPacket(static_cast<short>(400), static_cast<short>(7), data);
					std::vector<char> bytes = dataPacket->toByteArr();
								//        byte[] size = shortTObyte((short)400);
								//        byte[] Opcode = shortTObyte((short) 3);
								//        byte[] block = shortTObyte((short) 7);
								//        byte[] bytes = new byte[6 + 400];
								//        bytes[0] = Opcode[0] ; bytes[1] = Opcode[1] ; bytes[2] =  size[0] ; bytes[3] = size[1] ;bytes[4] = block[0] ;bytes[5] = block[1];
								//        for (int i = 6 ; i < bytes.length ; i++){
								//            bytes[i] = (byte) (rnd.nextInt(255) + 1);
								//        }

					for (int i = 0 ; i < bytes.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(bytes[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}
					std::wcout << std::wstring(L"DATAPacket - ");
					if (dynamic_cast<DATAPacket*>(tmp) != nullptr)
					{
						bool issame = true;
						for (int i = 0; i < data.size(); i++)
						{
							if (data[i] != (static_cast<DATAPacket*>(tmp))->getData()[i])
							{
								issame = false;
							}
						}

							std::wcout << (static_cast<DATAPacket*>(tmp))->getBlock() == static_cast<short>(7) && (static_cast<DATAPacket*>(tmp))->getPacketSize() == static_cast<short>(400) && issame << std::endl;

					}
					else
					{
						std::wcout << false << std::endl;
					}

				}

				void EncoderDecTest::DIRQtest()
				{
					Packet *tmp = nullptr;
					std::vector<char> Opcode = shortTObyte(static_cast<short>(6));
					DIRQPacket *dirqPacket = new DIRQPacket();
					Opcode = dirqPacket->toByteArr();
					for (int i = 0 ; i < 2 ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(Opcode[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"DIRQPacket - ");
					std::wcout << dynamic_cast<DIRQPacket*>(tmp) != nullptr << std::endl;
				}

				void EncoderDecTest::ACKTest()
				{
					Packet *tmp = nullptr;
								//        byte[] Opcode = shortTObyte((short) 4);
								//        byte[] block = shortTObyte((short) 0);
								//        byte[] bytes = new byte[] {Opcode[0] , Opcode[1] , block[0] , block[1]};
					ACKPacket *ackPacket = new ACKPacket(static_cast<short>(0));
					std::vector<char> bytes = ackPacket->toByteArr();
					for (int i = 0 ; i < 4 ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(bytes[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"ACKPacket - ");
					if (dynamic_cast<ACKPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<ACKPacket*>(tmp))->getBlock() == static_cast<short>(0) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}

				void EncoderDecTest::DISCTest()
				{
					Packet *tmp = nullptr;
					std::vector<char> Opcode = shortTObyte(static_cast<short>(10));
					DISCPacket *discPacket = new DISCPacket();
					Opcode = discPacket->toByteArr();

					for (int i = 0 ; i < 2 ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(Opcode[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"DISCPacket - ");
					std::wcout << dynamic_cast<DISCPacket*>(tmp) != nullptr << std::endl;
				}

				void EncoderDecTest::RRQTest()
				{
					Packet *tmp = nullptr;
					std::wstring fileName = L"I-have-a-programmer-hands";
					RRQPacket *rrqPacket = new RRQPacket(fileName);
								//        byte[] name = (fileName + '\0').getBytes();
								//        byte[] Opcode = shortTObyte((short) 1);
								//        byte[] bytes = new byte[2 + name.length];
								//        bytes[0] = Opcode[0] ; bytes[1] = Opcode[1];
								//        for (int i = 2 ; i < bytes.length ; i++){
								//            bytes[i] = name[i-2];
								//        }

					std::vector<char> bytes = rrqPacket->toByteArr();

					for (int i = 0 ; i < bytes.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(bytes[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}
					std::wcout << std::wstring(L"RRQPacket - ");
					if (dynamic_cast<RRQPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<RRQPacket*>(tmp))->getFileName().equals(fileName) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}

				void EncoderDecTest::WRQTest()
				{
					Packet *tmp = nullptr;
					std::wstring fileName = L"chocolate_or_strongberry";
					WRQPacket *wrqPacket = new WRQPacket(fileName);
								//        byte[] name = (fileName + '\0').getBytes();
								//        byte[] Opcode = shortTObyte((short) 2);
								//        byte[] bytes = new byte[2 + name.length];
								//        bytes[0] = Opcode[0] ; bytes[1] = Opcode[1];
								//        for (int i = 2 ; i < bytes.length ; i++){
								//            bytes[i] = name[i-2];
								//        }

					std::vector<char> bytes = wrqPacket->toByteArr();
					for (int i = 0 ; i < bytes.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(bytes[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"WRQPacket - ");
					if (dynamic_cast<WRQPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<WRQPacket*>(tmp))->getFileName().equals(fileName) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}

				void EncoderDecTest::DELRQtest()
				{
					Packet *tmp = nullptr;
					std::wstring fileName = L"Neto-Avoda";
								//        byte[] name = (fileName + '\0').getBytes();
								//        byte[] Opcode = shortTObyte((short) 8);
								//        byte[] bytes = new byte[2 + name.length];
								//        bytes[0] = Opcode[0] ; bytes[1] = Opcode[1];
								//        for (int i = 2 ; i < bytes.length ; i++){
								//            bytes[i] = name[i-2];
								//        }

					DELRQPacket *delrqPacket = new DELRQPacket(fileName);
					std::vector<char> bytes = delrqPacket->toByteArr();
					for (int i = 0 ; i < bytes.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(bytes[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"DELRQPacket - ");
					if (dynamic_cast<DELRQPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<DELRQPacket*>(tmp))->getFilename().equals(fileName) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}

				void EncoderDecTest::LOGRQtest()
				{
					Packet *tmp = nullptr;
					std::wstring nickName = L"Spl_Took_My_Life";
								//        byte[] name = (nickName + '\0').getBytes();
								//        byte[] Opcode = shortTObyte((short)7);
								//        byte[] bytes = new byte [2 + name.length];
								//        bytes[0] = Opcode[0] ; bytes [1] = Opcode[1];
								//        for (int i = 2 ; i < bytes.length ; i++){
								//            bytes[i] = name[i-2];
								//        }

					LOGRQPacket *logrqPacket = new LOGRQPacket(nickName);
					std::vector<char> bytes = logrqPacket->toByteArr();
					for (int i = 0 ; i < bytes.size() ; i++)
					{
						try
						{
							tmp = p->decodeNextByte(bytes[i]);
						}
						catch (const UnsupportedEncodingException &e)
						{
							e->printStackTrace();
						}
					}

					std::wcout << std::wstring(L"LOGRQPacket - ");
					if (dynamic_cast<LOGRQPacket*>(tmp) != nullptr)
					{
						std::wcout << (static_cast<LOGRQPacket*>(tmp))->getUserName().equals(nickName) << std::endl;
					}
					else
					{
						std::wcout << false << std::endl;
					}
				}
			}
		}
	}
}
