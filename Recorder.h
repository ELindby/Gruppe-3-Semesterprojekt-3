#pragma once
#include <SFML/Audio.hpp>

class DTMFRecorder : public sf::SoundRecorder
{
public:
	DTMFRecorder();
	~DTMFRecorder();

	virtual bool onStart();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	float goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<int>&windowedSignal);



private:
	int sampleRate = 8000;
	const std::vector<int> DTMFtones{ 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	int highL, highH;
};