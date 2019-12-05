#pragma once
#include <SFML/Audio.hpp>

class ProcessData
{
public:
	ProcessData();
	~ProcessData();

	void findFirstTone(std::vector<float>& recording);
	int determineDTMF(std::vector<float>& recording, bool findLow);
	float goertzel(int sampleCount, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<float>& recording);

private:
	const std::vector<int> DTMFtones{ 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	const int sampleRate = 8000;
};
