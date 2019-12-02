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
	SoundGenerator(std::vector<std::bitset<8>>& input);

	void convertToDTMF(std::vector<std::bitset<8>>& input);
	int lowtoneFrequency(char low);
	int hightoneFrequency(char high);
	void PlaySound(std::vector<float>&lowFrenquencies, std::vector<float>&highFrenquencies);

	sf::Int16 savedSignal;
	sf::SoundBuffer BufferL;
	sf::Sound SoundL;

private:
	const double pi = 3.14159265358979323846;
};

