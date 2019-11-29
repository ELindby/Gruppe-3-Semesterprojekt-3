#pragma once
#include <iostream>

#include "deframe.h"

class PackageCollector
{
public:
	PackageCollector();
	~PackageCollector();

	void AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram);
	void SendACK();
	void MessageToApp();
	std::vector<std::bitset<8>> packageContainer;

private:
	
};
