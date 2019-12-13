#pragma once
#include <iostream>
#include "Recorder.h"

class PackageCollector
{
public:
	PackageCollector();
	~PackageCollector();

	static bool static_spFlag; //sp flag, 0 during transmission, 1 when complete message has been recieved
	static std::vector<std::bitset<8>> packageContainer; //Recieved messages (without header/trailer)
	static void clearContainer();
	static std::vector<std::bitset<8>> GetMsg(); //Getter for the message stored

	void AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram); //Adds unpacked message to collector container
	void SendACK(); //Send Acknowledge package

private:
};