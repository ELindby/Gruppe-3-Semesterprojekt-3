#pragma once
#include <cassert>
#include <iostream>

class DTMFConverter 
{
public:
	DTMFConverter();
	~DTMFConverter();
	DTMFConverter(char input, int lowDTMFL, int lowDTMFU, int highDTMFL, int highDTMFU);

	int LowToneFrequency(char low);
	int HighToneFrequency(char high);
};
