#include "Recorder.h"
#include <iostream>
#include <numeric>
#include <bitset>
#include <cstdio>
#include <ctime>
#include <thread>

const double pi = 3.14159265358979323846;

DTMFRecorder::DTMFRecorder()
{
}

DTMFRecorder::~DTMFRecorder()
{
	stop();
}

bool DTMFRecorder::onStart()
{
	setProcessingInterval(sf::milliseconds(200 -5)); // Process data in intervals of X ms
	return true;
}

void DTMFRecorder::threadTest(int &a, int &b)
{
	a = a + b;

}

bool DTMFRecorder::onProcessSamples(const sf::Int16 * samples, std::size_t sampleCount)
{
	// time measurement
	//begin = std::clock();

	std::thread t1(&threadTest, 10, 5);

	// Multiply with Hann window
	std::vector<float> windowedSignal = hannWindow(samples, sampleCount);

	// Determine low and high frequency
	int freqL = determineDTMF(windowedSignal, true);
	int freqH = determineDTMF(windowedSignal, false);

	// Save data
	if (savingMessage == true)
	{
		saveRecording(freqL, freqH);
		convertFromDTMF(recordedMessage);
	}

	// if start signal is recorded -> start saving recordings
	if (savingMessage == false)
	{
		if (freqL == 941 && freqH == 1633)
		{
			if (lastFreqL == freqL && lastFreqH == freqH)
			{
				savingMessage = true;
				std::cout << "start signal heard" << std::endl;
			}
		}
	}

	//time measurement
	//duration = (std::clock() - begin) / (double)CLOCKS_PER_SEC;
	//std::cout <<  duration << '\n';

	// Temporarily save this data
	lastFreqL = freqL;
	lastFreqH = freqH;

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
	recordedMessage.push_back(lowFreq);
	recordedMessage.push_back(highFreq);
}

int DTMFRecorder::determineDTMF(std::vector<float>& recording, bool findLow)
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

	if ((magnitudesL[indexL] > (sum_of_magnitudes / 3)) || (magnitudesH[indexH - 4] > (sum_of_magnitudes / 3)))
	{
		if (magnitudesL[indexL] > magnitudesH[indexH - 4])
		{
			if ( magnitudesH[indexH - 4] > (magnitudesL[indexL] / 2))
			{
				if (findLow == true)
					return freqL;
				else {
					return freqH;
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
						return freqL;
					else {
						return freqH;
					}
				}
			}
		}
	}
		return 0;


	//// Accept only result if magnitude > sum/4
	//if ((magnitudesL[indexL] > (sum_of_magnitudes / 4)) or (magnitudesH[indexH - 4] > (sum_of_magnitudes / 4))) // fix "or"
	//{

	//	if (magnitudesL[indexL] > magnitudesH[indexH - 4])
	//	{
	//		if ((magnitudesL[indexL] > (sum_of_magnitudes / 4)) and (magnitudesH[indexH - 4] > (magnitudesL[indexL] / 2)))
	//		{
	//			//if (findLow == true) {
	//			//	return freqL;
	//			//}
	//			//else {
	//			//	return freqH;
	//			//}
	//			return 1;
	//		}
	//	}

	//	else
	//	{
	//		if (magnitudesL[indexL] < magnitudesH[indexH - 4])
	//		{
	//			if ((magnitudesH[indexH - 4] > (sum_of_magnitudes / 4)) and ((magnitudesH[indexH - 4] / 2) < magnitudesL[indexL]))
	//			{
	//				//if (findLow == true) {
	//				//	return freqL;
	//				//}
	//				//else {
	//				//	return freqH;
	//				//}
	//				return 2;
	//			}
	//		}
	//	}
	//}

	//else {
	//	return 0;
	//}
}

void DTMFRecorder::convertFromDTMF(std::vector<int>recordedMessage)
{
	std::vector<char> unwrappedMessage;

	// Combine 4 frequencies to a single character
	for (int i = 0; i < (recordedMessage.size() / 4); i++)
	{
		int binaryValue = 0b00000000;

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

		// Save it all in a vector
		char asChar = binaryValue;

		unwrappedMessage.push_back(asChar);
	}

	// Print message
	for (int i = 0; i < unwrappedMessage.size(); i++)
	{
		std::cout << unwrappedMessage[i];
		//std::cout << std::bitset<8>(unwrappedMessage[i]);
	}

	std::cout << std::endl;

}


