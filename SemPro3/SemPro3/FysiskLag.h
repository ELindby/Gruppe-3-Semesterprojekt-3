#pragma once
#include "DTMFConverter.h"
#include "ToneGenerator.h"

class FysiskLag
{
public:
	FysiskLag();
	~FysiskLag();
	FysiskLag(char input);

protected:
	int lowDTMFL, highDTMFL, lowDTMFU, highDTMFU;
};
