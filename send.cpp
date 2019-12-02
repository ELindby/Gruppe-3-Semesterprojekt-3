#include "send.h"

Send::Send(){}
Send::~Send() {}

Send::Send(char n){
	ConvertToDTMF(n);
}

void Send::ConvertToDTMF(char input){
	// Masks upper and lower nipple of ASCII byte
	char lowerNipple = 0b00001111 & input;
	char upperNipple = (0b11110000 & input) >> 4;

	// Finds DTMF tone for lower nipple
	int lowDTMFL = lowtoneFrequency(lowerNipple);
	int highDTMFL = hightoneFrequency(lowerNipple);

	// Finds DTMF tone for upper nipple
	int lowDTMFU = lowtoneFrequency(upperNipple);
	int highDTMFU = hightoneFrequency(upperNipple);

	// Displays information at terminal
	std::cout << input << ": " << '\n' << lowDTMFL << '\t' << highDTMFL << '\n';
	std::cout << lowDTMFU << '\t' << highDTMFU << std::endl;

	PlaySound(lowDTMFL, highDTMFL, lowDTMFU, highDTMFU);
}
int Send::lowtoneFrequency(char low){
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
int Send::hightoneFrequency(char high){
	assert(high < 16);
	int highDTMF = 0;
	int col = (high + 1) % 4;

	switch (col)
	{
	case 1:
		return highDTMF = 1209;
	case 2:
		return highDTMF = 1336;
	case 3:
		return highDTMF = 1477;
	case 0:
		return highDTMF = 1633;
	}
}
void Send::PlaySound(int lowDTMFL, int highDTMFL, int lowDTMFU, int highDTMFU){
	// Sample sinewave
	const unsigned wSampleRate = 8000;
	const unsigned nSamples = 8000;

	sf::Int16 toneL[nSamples];
	sf::Int16 toneU[nSamples];
	const double twoPi = 6.28318;
	double piPoduct1L = (twoPi * lowDTMFL) / wSampleRate;
	double piPoduct2L = (twoPi * highDTMFL) / wSampleRate;

	double piPoduct1U = (twoPi * lowDTMFU) / wSampleRate;
	double piPoduct2U = (twoPi * highDTMFU) / wSampleRate;

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

	sf::sleep(sf::milliseconds(1000));

	sf::Sound SoundU;
	SoundU.setBuffer(BufferU);
	SoundU.setLoop(true);
	SoundU.play();

	sf::sleep(sf::milliseconds(1000));
}
