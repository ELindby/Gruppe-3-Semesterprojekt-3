#pragma once
#include "DTMFConverter.h"
#include "ToneGenerator.h"

#ifndef FYSISKLAG_H
#define FYSISKLAG_H

class FysiskLag
{
public:
	FysiskLag();
	~FysiskLag();
	FysiskLag(char input);

protected:
	int lowDTMFL, highDTMFL, lowDTMFU, highDTMFU;
};
#endif // FYSISKLAG_H
