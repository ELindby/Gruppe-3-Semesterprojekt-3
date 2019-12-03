#pragma once
#include <iostream>

#include "Recorder.h"

class PackageCollector
{
public:
	PackageCollector();
	~PackageCollector();

	static std::vector<std::bitset<8>> packageContainer;

	void AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram);
	void MessageToApp();
	void SendACK();

private:
};