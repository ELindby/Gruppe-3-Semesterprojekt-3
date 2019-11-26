#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class ToneGenerator
{
public:
	ToneGenerator();
	~ToneGenerator();
	ToneGenerator(int lowDTMFL, int lowDTMFU, int highDTMFL, int highDTMFU);
	void PlaySound(int lowDTMFL, int lowDTMFU, int highDTMFL, int highDTMFU);
};
