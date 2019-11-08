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
	int lowDTMFL, highDTMFL, lowDTMFU, highDTMFU;
};
