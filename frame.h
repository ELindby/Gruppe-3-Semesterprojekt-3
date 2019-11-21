#pragma once
#include <iostream>

#include <math.h>
#include <vector>
#include <array>
#include <bitset>


class Frame
{
public:
	Frame();
	~Frame();

	void MessageCutter(char message[]); //Del beskeden op i bider af data
	void AddTrailer();

	std::vector<std::vector<std::bitset<8>>> GetPackages();

	void PrintMsgSliced();

private:

	std::vector<std::vector<std::bitset<8>>> slicedMessage;

	const int maxDataSize = 31; //Antal bytes i datagrammet.

	//Til header_____________
	std::bitset<8> AddHeader(bool lastPackage, int size);

	std::bitset<1> sq = 0; //seq. nr. bit
	std::bitset<5> dataSize; //Antal bytes i pakken
	std::bitset<1> sp; //sidste pakke flag

	//Til trailer____________
};