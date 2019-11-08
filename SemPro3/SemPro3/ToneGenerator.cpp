#include "ToneGenerator.h"

ToneGenerator::ToneGenerator() {
	PlaySound();
}
ToneGenerator::~ToneGenerator() {}

void ToneGenerator::PlaySound() {
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
	// Play tone for some time
	sf::sleep(sf::milliseconds(400));

	sf::Sound SoundU;
	SoundU.setBuffer(BufferU);
	SoundU.setLoop(true);
	SoundU.play();
	//// Play tone for some time
	sf::sleep(sf::milliseconds(400));
}
