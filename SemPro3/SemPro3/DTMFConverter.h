#pragma once
#include "PhysicalLayer.h"
#include <cassert>
#include <iostream>


class DTMFConverter : public PhysicalLayer
{
public:
	DTMFConverter();
	~DTMFConverter();
	DTMFConverter(char input);

	int LowToneFrequency(char low);
	int HighToneFrequency(char high);
};
