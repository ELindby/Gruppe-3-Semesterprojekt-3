#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <bitset>

#include "crc.h"

class DeFrame
{
public:
	DeFrame();
	~DeFrame();

	CRC crcClass;

	static bool ack; //Is true if package is an acknowledge

	void UnPack(std::vector<std::bitset<8>> package);
	std::vector<std::bitset<8>> getDatagram();

	//Getters
	bool getAckFlag();
	bool getSpFlag();
	bool DoubletCheck();
	bool CrcCheck();

private:

	//Header information
	void Hi(std::bitset<8> package); //Sets Header Information from package
	std::bitset<8> header;
	bool sq = 0; //sq flag, represents the sequence number
	int dataSize; //Amount of bytes in package
	bool sp = 0; //sp flag, 1 for last package in a transmission, 0 for all others

	
	std::vector<std::bitset<8>> datagram; //Datagram (payload)

	bool oldsq = 0; //Used for dublet check, sq flag of previous package recieved

	std::bitset<8> trailer; //Package trailer, contains CRC codeword and used for CRC check
};