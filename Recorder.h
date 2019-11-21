#pragma once
#include <SFML/Audio.hpp>
#include "ProcessData.h"

class DTMFRecorder : public sf::SoundRecorder
{
public:
	DTMFRecorder();
	~DTMFRecorder();

	virtual bool onStart();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	float goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<float>&windowedSignal);
	std::vector<float> hannWindow(const sf::Int16 * samples, std::size_t sampleCount);
	void saveRecording(int lowFreq, int highFreq);
	int determineDTMF(std::vector<float>& recording, bool findLow);
	void convertFromDTMF(std::vector<int> recordedMessage);


private:
	const int sampleRate = 8000;
	const std::vector<int> DTMFtones{ 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	std::vector<int> recordedMessage;
	int highL, highH;
	int lastFreq;
	int processCounter;
	bool savingMessage = false;
};