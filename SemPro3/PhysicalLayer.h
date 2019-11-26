#pragma once
#include "DTMFConverter.h"
#include "ToneGenerator.h"

class PhysicalLayer
{
public:
	PhysicalLayer();
	~PhysicalLayer();
	PhysicalLayer(char input);

protected:
	int LL = 0, HL = 0, LU = 0, HU = 0;

	int* lowDTMFL = &LL;
	int* highDTMFL = &HL;
	int* lowDTMFU = &LU;
	int* highDTMFU = &HU;
};
