#include "SoundGenerator.h"
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

#include <cstdio>
#include <ctime>

SoundGenerator::SoundGenerator()
{
}

SoundGenerator::~SoundGenerator()
{
}

SoundGenerator::SoundGenerator(std::vector<std::bitset<8>>& message)
{
	convertToDTMF(message);
}

void SoundGenerator::convertToDTMF(std::vector<std::bitset<8>>& input)
{
	std::vector<float> highFrequencies;
	std::vector<float> lowFrequencies;

	// Add start signal
	lowFrequencies.push_back(941);
	highFrequencies.push_back(1633);
	lowFrequencies.push_back(941);
	highFrequencies.push_back(1633);

	// Add message
	for (int i = 0; i < (input.size()); i++) {

		// Masks upper and lower nipple of ASCII byte
		int lowerNipple = 0b00001111  & input[i].to_ulong();
		int upperNipple = (0b11110000 & input[i].to_ulong()) >> 4;

		// Finds DTMF tone for lower nipple
		int lowDTMFL = lowtoneFrequency(lowerNipple);
		int highDTMFL = hightoneFrequency(lowerNipple);

		// Finds DTMF tone for upper nipple
		int lowDTMFU = lowtoneFrequency(upperNipple);
		int highDTMFU = hightoneFrequency(upperNipple);

		// Put lower frequencies in a vector
		lowFrequencies.push_back(lowDTMFL);
		lowFrequencies.push_back(lowDTMFU);

		// Put high frequencies in another vector
		highFrequencies.push_back(highDTMFL);
		highFrequencies.push_back(highDTMFU);
	}

	// Add end signal
	lowFrequencies.push_back(697);
	highFrequencies.push_back(1209);
	lowFrequencies.push_back(697);
	highFrequencies.push_back(1209);

	// Play DTMF tones
	PlaySound(lowFrequencies, highFrequencies);
}

int SoundGenerator::lowtoneFrequency(char low) {
	assert(low < 16);
	int lowDTMF = 0;
	if (low < 12) {
		if (low < 8) {
			if (low < 4) {
				return lowDTMF = 697;
			}
			return lowDTMF = 770;
		}
		return lowDTMF = 852;
	}
	return lowDTMF = 941;
}

int SoundGenerator::hightoneFrequency(char high) {
		assert(high < 16);
		int highDTMF = 0;
		int col = (high + 1) % 4;

		switch (col)
		{
		case 1:
			return highDTMF = 1209;
			break;
		case 2:
			return highDTMF = 1336;
			break;
		case 3:
			return highDTMF = 1477;
			break;
		case 0:
			return highDTMF = 1633;
			break;
		}
}

void SoundGenerator::PlaySound(std::vector<float>& lowFrequencies, std::vector<float>& highFrequencies)
{
	// Sample sinewave (method 1)
	const unsigned wSampleRate = 22000;
	const unsigned nSamples = 22000;

	sf::Int16 toneL[nSamples];

	const double twoPi = 6.28318;

	for (int i = 0; i < (lowFrequencies.size()); i++)
	{
		std::clock_t start; // Measure time to generate signal
		float duration;
		start = std::clock();

		double piPoduct1L = (twoPi * lowFrequencies[i]) / wSampleRate;

		double piPoduct1U = (twoPi * highFrequencies[i]) / wSampleRate;

		for (unsigned i = 0; i < nSamples; i++) {
			toneL[i] = 128 * (63 * sin(i * piPoduct1L) + 63 * sin(i * piPoduct1U));
		}

		duration = ((std::clock() - start) / (float)CLOCKS_PER_SEC) * 1000; // Save time measured

		// Play DTMF tone (sinewave)
		if ((!BufferL.loadFromSamples(toneL, nSamples, 1, wSampleRate))) {
			std::cerr << "Loading failed!" << std::endl;
		}
			SoundL.setBuffer(BufferL);
			SoundL.setLoop(true);
			SoundL.play();
			sf::sleep(sf::milliseconds(60));
			SoundL.stop();
			sf::sleep(sf::milliseconds(190 - duration)); // "pad" the signal with silence
		}

}