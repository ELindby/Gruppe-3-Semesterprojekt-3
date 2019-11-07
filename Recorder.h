#pragma once
#include <SFML/Audio.hpp>

class DTMFRecorder : public sf::SoundRecorder
{
public:
	DTMFRecorder();
	~DTMFRecorder();

	virtual bool onStart();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	float goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, const sf::Int16* data);

	int* hammingWindow(int *window);
};