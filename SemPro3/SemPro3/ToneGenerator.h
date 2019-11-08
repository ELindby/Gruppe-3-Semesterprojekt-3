#pragma once
#include "PhysicalLayer.h"
#include <SFML/Audio.hpp>
#include <iostream>

class ToneGenerator : public PhysicalLayer
{
public:
	ToneGenerator();
	~ToneGenerator();

	void PlaySound();
};
