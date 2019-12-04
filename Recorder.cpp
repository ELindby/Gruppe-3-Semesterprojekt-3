#include "Recorder.h"
#include <iostream>
#include <numeric>
#include <bitset>
#include <cstdio>
#include <ctime>
#include <thread>

bool DTMFRecorder::pauseRecording = false;
bool DTMFRecorder::static_syncing = true;

DTMFRecorder::DTMFRecorder()
{
}

DTMFRecorder::~DTMFRecorder()
{
	stop();
}

bool DTMFRecorder::onStart()
{
	setProcessingInterval(sf::milliseconds(processInterval)); // Process data in intervals of X ms
	sync = true; // start sync
	return true;
}

void DTMFRecorder::determineLow()
{
	determineDTMF(windowedSignal, true);
};

void DTMFRecorder::determineHigh()
{
	determineDTMF(windowedSignal, false);
};

bool DTMFRecorder::onProcessSamples(const sf::Int16 * samples, std::size_t sampleCount)
{
	if (pauseRecording == true)
	{
		return true;
	}

	// start timer
	if (sync == true)
	{
		begin = std::clock();
	}

	// Multiply with Hann window
	windowedSignal = hannWindow(samples, sampleCount);

	std::thread t1(&DTMFRecorder::determineLow, this);
	std::thread t2(&DTMFRecorder::determineHigh, this);

	// wait for thread to finish
	t1.join();
	t2.join();

	// Save data
	if (savingMessage == true)
	{
		saveRecording(currentFreqL, currentFreqH);
		// convertFromDTMF(recordedMessage);
			if (currentFreqL == 697 && currentFreqH == 1209)
			{
				if (lastFreqL == 697 && lastFreqH == 1209)
				{
					savingMessage = false;
					std::cout << "Stop saving" << std::endl;
					compareTones = false;

					convertFromDTMF(saveBuffer);
				}
			}
	}

	// if start signal is recorded -> start saving recordings
	if (savingMessage == false)
	{
		if (currentFreqL == 941 && currentFreqH == 1633)
		{
			if (lastFreqL == 941 && lastFreqH == 1633)
			{
				savingMessage = true;
				std::cout << "Start saving" << std::endl;
				compareTones == true;
			}
		}
	}

	// If no dtmf tones heard -> false alarm -> stop saving
	if (savingMessage == true)
	{
		if (currentFreqL == 0 && currentFreqH == 0)
		{
			if (lastFreqL == 0 && lastFreqH == 0)
			{
				std::cout << "false alarm" << std::endl;
				savingMessage = false;
				saveBuffer.clear(); // clear buffer
				
			}
		}
	}

	compareTones = !compareTones;

	// Temporarily save this data
	lastFreqL = currentFreqL;
	lastFreqH = currentFreqH;

	//// Constant Synchronization
	//if(sync == true)
	//{
	//	duration = ((std::clock() - begin) / (double)CLOCKS_PER_SEC)*1000;
	//	setProcessingInterval(sf::milliseconds(processInterval - avgProcessTime));
	//	// std::cout << "Process time " << duration << " milliseconds" << std::endl;
	//	// std::cout << "Next interval is " << processInterval - duration << " milliseconds" << std::endl;

	//}

	// Fixed Synchronization
	if (sync == true)
	{
		int timesToMeasure = 10;

		if (syncCounter < timesToMeasure)
		{
			duration = (std::clock() - begin) / (double)CLOCKS_PER_SEC;
			std::cout << duration << '\n';

			avgProcessTime = avgProcessTime + duration;
			syncCounter = syncCounter + 1;
			std::cout << "synchronizing ..." << std::endl;
		}
		if (syncCounter == timesToMeasure)
		{
			avgProcessTime = (avgProcessTime / timesToMeasure)*1000;
			setProcessingInterval(sf::milliseconds(processInterval - avgProcessTime));
			std::cout << "Sync done. Avg process time: " << avgProcessTime << " milliseconds" << std::endl;
			std::cout << "Process interval set to:" << processInterval - avgProcessTime << " milliseconds" << std::endl;
			sync = false;
			DTMFRecorder::static_syncing = sync;
		}
	}
	return true; // continue recording
}

float DTMFRecorder::goertzel(std::size_t sampleCount, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<float>&windowedSignal)
{
	int     k, i;
	float   floatnumSamples;
	float   omega, sine, cosine, coeff, q0, q1, q2, magnitude;

	floatnumSamples = (float)sampleCount;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * pi * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i < sampleCount; i++) {
		q0 = coeff * q1 - q2 + windowedSignal[i];
		q2 = q1;
		q1 = q0;
	}
	magnitude = sqrtf(pow(q1, 2) + pow(q2, 2) - q1 * q2 * coeff);
	return magnitude;
}


std::vector<float> DTMFRecorder::hannWindow(const sf::Int16 * samples, std::size_t sampleCount)
{
	// Apply Hann smoothing
	std::vector<float> windowedSignal;

	for (int i = 0; i < sampleCount; i++) {
		double multiplier = 0.5 * (1 - cos(2 * pi*i / (sampleCount - 1)));
		windowedSignal.push_back(multiplier * samples[i]);
	}
	return windowedSignal;
}

void DTMFRecorder::saveRecording(int lowFreq, int highFreq)
{
	// Save low frequency first, then high
	saveBuffer.push_back(lowFreq);
	saveBuffer.push_back(highFreq);
}

void DTMFRecorder::determineDTMF(std::vector<float>& recording, bool findLow)
{
	std::vector<float> magnitudesL, magnitudesH;
	int freqL = 0;
	int	freqH = 0;
	int indexL = 0;
	int	indexH = 4;

	// Lower half of tones
	for (int a = 0; a < 4; a++) {
		magnitudesL.push_back(goertzel(recording.size(), DTMFtones[a], sampleRate, recording));
	}

	for (unsigned int i = 0; i < 4; i++) {
		if (magnitudesL[i] > freqL) {
			freqL = magnitudesL[i];
			indexL = i;
		}
	}
	freqL = DTMFtones[indexL];

	// Higher half of tones
	for (int a = 0; a < 4; a++) {
		magnitudesH.push_back(goertzel(recording.size(), DTMFtones[a + 4], sampleRate, recording));
	}

	for (unsigned int i = 0; i < 4; i++) {
		if (magnitudesH[i] > freqH) {
			freqH = magnitudesH[i];
			indexH = i + 4;
		}
	}
	freqH = DTMFtones[indexH];


	// Determine if magnitude is high enough
	float sum_of_magnitudes;
	sum_of_magnitudes = (std::accumulate(magnitudesH.begin(), magnitudesH.end(), 0)) + (std::accumulate(magnitudesL.begin(), magnitudesL.end(), 0));

	if ((magnitudesL[indexL] > (sum_of_magnitudes / 4)) || (magnitudesH[indexH - 4] > (sum_of_magnitudes / 4)))
	{
		if (magnitudesL[indexL] > magnitudesH[indexH - 4])
		{
			if ( magnitudesH[indexH - 4] > (magnitudesL[indexL] / 2))
			{
				if (findLow == true)
					currentFreqL = freqL;
				else {
					currentFreqH = freqH;
				}
			}
		}

		else
		{
			if (magnitudesL[indexL] < magnitudesH[indexH - 4])
			{
				if ((magnitudesH[indexH - 4] / 2) < magnitudesL[indexL])
				{
					if (findLow == true)
						currentFreqL = freqL;
					else {
						currentFreqH = freqH;
					}
				}
			}
		}
	} 
	else {
		currentFreqL = 0;
		currentFreqH = 0;
	}
		return;
}

void DTMFRecorder::convertFromDTMF(std::vector<int>recordedMessage)
{
	// check if even number if nibbles has been received
	std::cout << recordedMessage.size() << std::endl;

	if (recordedMessage.size() % 4 == 0)
	{
		std::cout << "No error in physical layer" << std::endl;
	}
	else {
		std::cout << "Uneven number of tones heard" << std::endl;
	}

	std::vector<std::bitset<8>> unwrappedMessage;

	// Combine 4 frequencies to a single character
	for (int i = 0; i < (recordedMessage.size() / 4); i++)
	{
		std::bitset<8> binaryValue = 0b00000000;

		switch (recordedMessage[i * 4])
		{
		case 697:
			binaryValue = 0b00000000;
			break;
		case 770:
			binaryValue = 0b00000100;
			break;
		case 852:
			binaryValue = 0b00001000;
			break;
		case 941:
			binaryValue = 0b00001100;
			break;
		}

		switch (recordedMessage[i * 4 + 1])
		{
		case 1209:
			binaryValue |= 0b00000000;
			break;
		case 1336:
			binaryValue |= 0b00000001;
			break;
		case 1477:
			binaryValue |= 0b00000010;
			break;
		case 1633:
			binaryValue |= 0b00000011;
			break;
		}

		switch (recordedMessage[i * 4 + 2])
		{
		case 697:
			binaryValue |= 0b00000000;
			break;
		case 770:
			binaryValue |= 0b01000000;
			break;
		case 852:
			binaryValue |= 0b10000000;
			break;
		case 941:
			binaryValue |= 0b11000000;
			break;
		}

		switch (recordedMessage[i * 4 + 3])
		{
		case 1209:
			binaryValue |= 0b00000000;
			break;
		case 1336:
			binaryValue |= 0b00010000;
			break;
		case 1477:
			binaryValue |= 0b00100000;
			break;
		case 1633:
			binaryValue |= 0b00110000;
			break;
		}
		unwrappedMessage.push_back(binaryValue);
	}
	// Remove last element of vector (end signal)
	 unwrappedMessage.pop_back();

	// convert to char (for testing)
	std::vector<char> messageAsString;

	// Print message
	for (int i = 0; i < unwrappedMessage.size(); i++)
	{
		// std::cout << unwrappedMessage[i];
		unsigned long j = unwrappedMessage[i].to_ulong();
		messageAsString.push_back(static_cast<unsigned char>(j));
		std::cout << messageAsString[i];
		//std::cout << std::bitset<8>(unwrappedMessage[i]);
	}

	std::cout << std::endl;

	// clear buffer
	saveBuffer.clear();

	//deframe
	deframer.UnPack(unwrappedMessage);
}


