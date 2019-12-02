#pragma once
#include <iostream>

#include "package_sender.h"
#include "Recorder.h"

class PackageCollector
{
public:
	PackageCollector();
	~PackageCollector();

	void AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram);
	void MessageToApp();
	std::vector<std::bitset<8>> packageContainer;
	void SendACK();

private:
};