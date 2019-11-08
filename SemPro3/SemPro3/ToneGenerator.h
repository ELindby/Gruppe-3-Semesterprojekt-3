#pragma once
#include "FysiskLag.h"
#include <SFML/Audio.hpp>
#include <iostream>

class ToneGenerator : public FysiskLag
{
public:
	ToneGenerator();
	~ToneGenerator();

	void PlaySound();
};
