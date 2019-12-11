#pragma once
#include <SFML/Audio.hpp>

#include "ProcessData.h"
#include "deframe.h"

class DTMFRecorder : public sf::SoundRecorder
{
public:
	DTMFRecorder();
	~DTMFRecorder();

	virtual bool onStart();
	static bool pauseRecording;
	static bool static_syncing;

	void determineLow();
	void determineHigh();

	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	float goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<float>&windowedSignal);
	std::vector<float> hannWindow(const sf::Int16 * samples, std::size_t sampleCount);
	void saveRecording(int lowFreq, int highFreq);
	void determineDTMF(std::vector<float>& recording, bool findLow);
	void convertFromDTMF(std::vector<int> recordedMessage);

	DeFrame deframer;

private:
	const double pi = 3.14159265358979323846;
	const int sampleRate = 8000;
	const std::vector<int> DTMFtones{ 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	std::vector<int> saveBuffer;
	int highL, highH;
	int lastFreqL, lastFreqH;
	int processCounter;
	bool savingMessage = false;
	int currentFreqL, currentFreqH;
	std::vector<float> windowedSignal;
	int processInterval = 500;
	bool sync;
	float avgProcessTime = 0;
	int syncCounter = 0;
	bool compareTones = false;

	std::clock_t begin;
	float duration;
};