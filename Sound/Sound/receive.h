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
#include <iomanip>
#include <iterator>

#define PI acos(-1.0)
#define TWO_PI 2 * acos(-1.0)

class receive
{
public:
	receive();
	~receive();

	void HigestFreq(const sf::SoundBuffer buffer);
	float Goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, const sf::Int16* data);

private:
	const std::vector<int> DTMFtones{ 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	int highL, highH;
};
