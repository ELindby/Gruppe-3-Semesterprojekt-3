#pragma once
#include "FysiskLag.h"
#include <cassert>
#include <iostream>

#ifndef DTMFCONVERTER_H
#define DTMFCONVERTER_H

class DTMFConverter : public FysiskLag
{
public:
	DTMFConverter();
	~DTMFConverter();
	DTMFConverter(char input);

	int LowToneFrequency(char low);
	int HighToneFrequency(char high);
};
#endif // DTMFCONVERTER_H
