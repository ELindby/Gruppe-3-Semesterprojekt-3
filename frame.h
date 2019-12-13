#pragma once
#include <iostream>

#include <math.h>
#include <vector>
#include <array>
#include <bitset>
#include <string>

#include "crc.h"


class Frame
{
public:
	Frame();
	~Frame();

	void MessageCutter(std::vector<std::bitset<8>> message); //Cuts recieved message into the right size payloads, and incapsulates them in frames

	std::vector<std::vector<std::bitset<8>>> GetPackages(); //Getter for package framed

private:

	std::vector<std::vector<std::bitset<8>>> slicedMessage;

	const int maxDataSize = 20; //Datagram (payload) max length, how many characters can max. be stored in a package

	//Header
	std::bitset<8> AddHeader(bool lastPackage, int size); //Adds header to package

	static std::bitset<1> sq; //sq flag, represents the sequence number
	std::bitset<5> dataSize;  //Amount of bytes in package
	std::bitset<1> sp;		  //sp flag, 1 for last package in a transmission, 0 for all others

	//Trailer
	void AddTrailer(std::vector<std::bitset<8>> headerAndDatagram); //Adds trailer to package
	std::bitset<8> trailer = 0b11111111; //Temporary value
};