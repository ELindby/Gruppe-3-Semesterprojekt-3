#pragma once
#include <iostream>

#include <math.h>
#include <vector>
#include <array>
#include <bitset>

#include "crc.h"


class Frame
{
public:
	Frame();
	~Frame();

	void MessageCutter(char message[]); //Del beskeden op i bider af data

	std::vector<std::vector<std::bitset<8>>> GetPackages();

	void PrintMsgSliced();

private:

	std::vector<std::vector<std::bitset<8>>> slicedMessage;

	const int maxDataSize = 31; //Max antal bytes i datagrammet.

	//Til header_____________
	std::bitset<8> AddHeader(bool lastPackage, int size);

	std::bitset<1> sq = 0; //seq. nr. bit
	std::bitset<5> dataSize; //Antal bytes i pakken
	std::bitset<1> sp; //sidste pakke flag

	//Til trailer____________
	void AddTrailer(std::vector<std::bitset<8>> headerAndDatagram);
	std::bitset<8> crcCodeword = 0b11111111; //Midlertidig værdi
};