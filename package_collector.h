#pragma once
#include <iostream>

#include "Recorder.h"

class PackageCollector
{
public:
	PackageCollector();
	~PackageCollector();

	static bool static_spFlag;
	static std::vector<std::bitset<8>> packageContainer;
	static std::vector<std::bitset<8>> GetMsg();

	void AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram);
	void SendACK();

private:
};