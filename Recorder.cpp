#include "Recorder.h"
#include <iostream>

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
	setProcessingInterval(sf::milliseconds(100)); // Process data in intervals of 100 ms
	return true;
}

bool DTMFRecorder::onProcessSamples(const sf::Int16 * samples, std::size_t sampleCount)
{
	std::vector<float> magnitudesL, magnitudesH;



	// Perform Goertzel algorithm for all DTMF frequencies
	for (int a = 0; a < 4; a++) {
		magnitudesL.push_back(goertzel(sampleCount, DTMFtones[a], sampleRate, samples));
		magnitudesH.push_back(goertzel(sampleCount, DTMFtones[a + 4], sampleRate, samples));
	}

	// threshold bør være summen af alle magnitude / 4

	// Find index of the highest frequency
	float freqL = 0, freqH = 0;
	int indexL = 0, indexH = 0;

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

	std::cout << freqL << std::endl << freqH << std::endl << std::endl;;

	return true; // continue recording

}

float DTMFRecorder::goertzel(std::size_t sampleCount, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, const sf::Int16 * samples)
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
		q0 = coeff * q1 - q2 + samples[i];
		q2 = q1;
		q1 = q0;
	}
	magnitude = sqrtf(pow(q1, 2) + pow(q2, 2) - q1 * q2 * coeff);
	return magnitude;
}