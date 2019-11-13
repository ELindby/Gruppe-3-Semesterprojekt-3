#include "SoundGenerator.h"
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

SoundGenerator::SoundGenerator()
{
}


SoundGenerator::~SoundGenerator()
{
}

SoundGenerator::SoundGenerator(std::string message)
{
	convertToDTMF(message);
}

void SoundGenerator::convertToDTMF(std::string& input)
{
	std::vector<int> highFrequencies;
	std::vector<int> lowFrequencies;

	for (int i = 0; i < (input.length()); i++) {

		// Masks upper and lower nipple of ASCII byte
		char lowerNipple = 0b00001111 & input[i];
		char upperNipple = (0b11110000 & input[i]) >> 4;


		// Finds DTMF tone for lower nipple
		int lowDTMFL = lowtoneFrequency(lowerNipple);
		int highDTMFL = hightoneFrequency(lowerNipple);


		// Finds DTMF tone for upper nipple
		int lowDTMFU = lowtoneFrequency(upperNipple);
		int highDTMFU = hightoneFrequency(upperNipple);

		// Put lower frequencies in a vector
		lowFrequencies.push_back(lowDTMFL);
		lowFrequencies.push_back(highDTMFL);

		// Put high frequencies in another vector
		highFrequencies.push_back(lowDTMFU);
		highFrequencies.push_back(highDTMFU);

		//// Displays information at terminal
		//std::cout << input << ": " << '\n' << lowDTMFL << '\t' << highDTMFL << '\n';
		//std::cout << lowDTMFU << '\t' << highDTMFU << std::endl;
	}

	//Play DTMF tones
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

	void SoundGenerator::PlaySound(std::vector<int>& lowFrequencies, std::vector<int>& highFrequencies)
	{
		// Sample sinewave
		const unsigned wSampleRate = 8000;
		const unsigned nSamples = 8000;

		sf::Int16 toneL[nSamples];
		sf::Int16 toneU[nSamples];
		const double twoPi = 6.28318;

		for (int i = 0; i < (lowFrequencies.size()/2); i++)
		{
			double piPoduct1L = (twoPi * lowFrequencies[i*2]) / wSampleRate;
			double piPoduct2L = (twoPi * lowFrequencies[(i*2)+1]) / wSampleRate;

			double piPoduct1U = (twoPi * highFrequencies[i * 2]) / wSampleRate;
			double piPoduct2U = (twoPi * highFrequencies[(i * 2) + 1]) / wSampleRate;

			for (unsigned i = 0; i < nSamples; i++) {
				toneL[i] = 128 * (63 * sin(i * piPoduct1L) + 63 * sin(i * piPoduct2L));
			}
			for (unsigned i = 0; i < nSamples; i++) {
				toneU[i] = 128 * (63 * sin(i * piPoduct1U) + 63 * sin(i * piPoduct2U));
			}

			// Play DTMF tone (sinewave)
			sf::SoundBuffer BufferL;
			sf::SoundBuffer BufferU;
			if ((!BufferL.loadFromSamples(toneL, nSamples, 1, wSampleRate)) & (!BufferU.loadFromSamples(toneU, nSamples, 1, wSampleRate))) {
				std::cerr << "Loading failed!" << std::endl;
			}

			sf::Sound SoundL;
			SoundL.setBuffer(BufferL);
			SoundL.setLoop(true);
			SoundL.play();
			sf::sleep(sf::milliseconds(400));

			SoundL.stop();

			sf::Sound SoundU;
			SoundU.setBuffer(BufferU);
			SoundU.setLoop(true);
			SoundU.play();

			sf::sleep(sf::milliseconds(400));
			SoundU.stop();

		}
	}
