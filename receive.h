#pragma once
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>

class receive
{
public:
	receive();
	~receive();

	float goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, const sf::Int16* data);
};