#pragma once
#include "FysiskLag.h"
#include <cassert>
#include <iostream>


class DTMFConverter : public FysiskLag
{
public:
	DTMFConverter();
	~DTMFConverter();
	DTMFConverter(char input);

	int LowToneFrequency(char low);
	int HighToneFrequency(char high);
};
