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

class SoundGenerator
{
public:
	SoundGenerator();
	~SoundGenerator();
	SoundGenerator(std::string message);

	void convertToDTMF(std::string& input);
	int lowtoneFrequency(char low);
	int hightoneFrequency(char high);
	void PlaySound(std::vector<int>&lowFrenquencies, std::vector<int>&highFrenquencies);
};

