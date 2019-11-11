#include "Recorder.h"
#include <iostream>
#include <numeric>

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
	setProcessingInterval(sf::milliseconds(400)); // Process data in intervals of 100 ms
	return true;
}

bool DTMFRecorder::onProcessSamples(const sf::Int16 * samples, std::size_t sampleCount)
{
	// Apply Hann smoothing
	std::vector<int> windowedSignal;

	for (int i = 0; i < sampleCount; i++) {
		double multiplier = 0.5 * (1 - cos(2 * pi*i / (sampleCount-1)));
		windowedSignal.push_back(multiplier * samples[i]);
	}

	// Perform Goertzel algorithm for all DTMF frequencies
	std::vector<float> magnitudesL, magnitudesH;

	for (int a = 0; a < 4; a++) {
		magnitudesL.push_back(goertzel(sampleCount, DTMFtones[a], sampleRate, windowedSignal));
		magnitudesH.push_back(goertzel(sampleCount, DTMFtones[a + 4], sampleRate, windowedSignal));
	}

	// Find index of the highest frequency
	float freqL = 0, freqH = 0;
	int indexL = 0, indexH = 4;

	for (unsigned int i = 0; i < 4; i++) {
		if (magnitudesL[i] > freqL) {
			freqL = magnitudesL[i];
			indexL = i;
		}
		if (magnitudesH[i] > freqH) {
			freqH = magnitudesH[i];
			indexH = i + 4;
		}
	}
	freqL = DTMFtones[indexL];
	freqH = DTMFtones[indexH];

	// Calculate magnitude threshold
	float sum_of_magnitudes;
	sum_of_magnitudes = (std::accumulate(magnitudesH.begin(), magnitudesH.end(), 0)) + (std::accumulate(magnitudesL.begin(), magnitudesL.end(), 0));


	if (magnitudesL[indexL] > magnitudesH[indexH-4])
	{
		if (magnitudesL[indexL] > (sum_of_magnitudes / 4) && magnitudesH[indexH - 4] > (magnitudesL[indexL]/2))
		{
			std::cout << freqL << " : " << magnitudesL[indexL] << std::endl << freqH << " : " << magnitudesH[indexH-4] << std::endl << std::endl;
		}
	}

	if (magnitudesL[indexL] < magnitudesH[indexH - 4])
	{
		if (magnitudesH[indexH-4] > (sum_of_magnitudes / 4) && (magnitudesH[indexH - 4]/2) < magnitudesL[indexL])
		{
			std::cout << freqL << " : " << magnitudesL[indexL] << std::endl << freqH << " : " << magnitudesH[indexH-4] << std::endl << std::endl;
		}
	}


	// std::cout << sum_of_magnitudes << std::endl;

	//// if start signal is recorded -> do something
	//if (freqL == 941 && freqH == 1477)
	//{
	//	std::cout << "nemlig";
	//	return false;
	//}

	return true; // continue recording

}

float DTMFRecorder::goertzel(std::size_t sampleCount, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<int>&windowedSignal)
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