#include "SoundGenerator.h"
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>

#include <cstdio>
#include <ctime>

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
	std::vector<float> highFrequencies;
	std::vector<float> lowFrequencies;

	//input start signal
	lowFrequencies.push_back(941);
	highFrequencies.push_back(1633);
	lowFrequencies.push_back(941);
	highFrequencies.push_back(1633);


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
		lowFrequencies.push_back(lowDTMFU);

		// Put high frequencies in another vector
		highFrequencies.push_back(highDTMFL);
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

//void SoundGenerator::PlaySound(std::vector<float>& lowFrequencies, std::vector<float>& highFrequencies)
//{
//	// Sample sinewave
//	const unsigned wSampleRate = 8000;
//	const unsigned nSamples = 8000;
//	const unsigned AMPLITUDE = 10000;
//
//	sf::Int16 toneL[nSamples];
//	sf::Int16 toneU[nSamples];
//	const double twoPi = 6.28318;
//
//	for (int i = 0; i < (lowFrequencies.size() / 2); i++)
//	{
//		float x = 0;
//		float y = 0;
//
//		const double TWO_PI = 6.28318;
//
//		for (unsigned n = 0; n < nSamples; n++) {
//			toneL[n] = (AMPLITUDE * sin(x*twoPi)) + (AMPLITUDE * sin(y*twoPi));
//			x += lowFrequencies[i * 2] / wSampleRate;
//			y += lowFrequencies[(i * 2) + 1] / wSampleRate;
//		}
//
//		for (unsigned n = 0; n < nSamples; n++) {
//			toneU[n] = (AMPLITUDE * sin(x*twoPi)) + (AMPLITUDE * sin(y*twoPi));
//			x += highFrequencies[i * 2] / wSampleRate;
//			y += highFrequencies[(i * 2) + 1] / wSampleRate;
//		}
//
//		// Play DTMF tone (sinewave)
//		sf::SoundBuffer BufferL;
//		sf::SoundBuffer BufferU;
//		if ((!BufferL.loadFromSamples(toneL, nSamples, 1, wSampleRate)) & (!BufferU.loadFromSamples(toneU, nSamples, 1, wSampleRate))) {
//			std::cerr << "Loading failed!" << std::endl;
//		}
//
//		sf::Sound SoundL;
//		SoundL.setBuffer(BufferL);
//		SoundL.setLoop(true);
//		SoundL.play();
//		sf::sleep(sf::milliseconds(240));
//
//		SoundL.stop();
//		sf::sleep(sf::milliseconds(10));
//
//		sf::Sound SoundU;
//		SoundU.setBuffer(BufferU);
//		SoundU.setLoop(true);
//		SoundU.play();
//
//		sf::sleep(sf::milliseconds(240));
//		SoundU.stop();
//		sf::sleep(sf::milliseconds(10));
//
//	}
//}


	void SoundGenerator::PlaySound(std::vector<float>& lowFrequencies, std::vector<float>& highFrequencies)
	{
		//std::clock_t start;
		//double duration;
		//start = std::clock();

		// Sample sinewave
		const unsigned wSampleRate =8000;
		const unsigned nSamples = 8000;

		sf::Int16 toneL[nSamples];

		const double twoPi = 6.28318;

			for (int i = 0; i < (lowFrequencies.size()); i++)
			{
				double piPoduct1L = (twoPi * lowFrequencies[i]) / wSampleRate;

				double piPoduct1U = (twoPi * highFrequencies[i]) / wSampleRate;

				for (unsigned i = 0; i < nSamples; i++) {
					toneL[i] = 128 * (63 * sin(i * piPoduct1L) + 63 * sin(i * piPoduct1U));
				}

				//// Create file with samples
				//std::ofstream outfile;
				//outfile.open("sample_1.csv");
				//for (size_t i = 0; i < nSamples; i++)
				//{
				//	//std::cout << DTMFtone[i] << '\t';
				//	outfile << i + 1 << ";";
				//	outfile << toneL[i] << std::endl;
				//}
				//outfile.close();

				// Play DTMF tone (sinewave)
				if ((!BufferL.loadFromSamples(toneL, nSamples, 1, wSampleRate)))  {
					std::cerr << "Loading failed!" << std::endl;
				}

				SoundL.setBuffer(BufferL);
				SoundL.setLoop(true);
				SoundL.play();
				sf::sleep(sf::milliseconds(50));

				SoundL.stop();
				sf::sleep(sf::milliseconds(150 - 2));

				//duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				//std::cout << "printf: " << duration << '\n';

			}
	}
