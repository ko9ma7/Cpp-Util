#pragma once
#include "NS.h"

NS_SOCKET_BEGIN
#pragma pack(1)
class Packet
{
public:
	char Tag;
	unsigned short Mark;
	char Vertify;
	unsigned int DataSize;
	unsigned short Protocol;
	unsigned short ErrorCode;
	unsigned short Reserved_0;
	unsigned short Reserved_1;
};
NS_SOCKET_END