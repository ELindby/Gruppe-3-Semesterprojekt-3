#pragma once
#include <math.h>
#include <vector>
#include <array>
#include <bitset>

class DataLinkLayer
{
public:
	DataLinkLayer();
	~DataLinkLayer();

	DataLinkLayer(std::vector<std::bitset<8>>);


};


// Framer og Deframer (names in progress)