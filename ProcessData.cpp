#include "ProcessData.h"
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>

const double pi = 3.14159265358979323846;

ProcessData::ProcessData()
{
}


ProcessData::~ProcessData()
{
}

void ProcessData::findFirstTone(std::vector<float>& recording)
{
	int windowLength = (8000 / 4);
	int windowCounter = 0;
	std::vector<float> tempData;

	for (int i = 0; i < recording.size() / 10; i++)
	{
		for (int j = 0; i < windowLength; i++) {
			tempData[j] = recording[i];
		}

		
	}
}

int ProcessData::determineDTMF(std::vector<float>& recording, bool findLow)
{
	std::vector<float> magnitudesL, magnitudesH;
	int freqL = 0;
	int	freqH = 0;
	int indexL = 0;
	int	indexH = 0;

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
		return freqL;

		// Higher half of tones
		for (int a = 0; a < 4; a++) {
			magnitudesH.push_back(goertzel(recording.size(), DTMFtones[a+4], sampleRate, recording));
		}

		for (unsigned int i = 0; i < 4; i++) {
			if (magnitudesH[i] > freqH) {
				freqH = magnitudesH[i];
				indexH = i + 4;
			}
		}

		freqH = DTMFtones[indexH];
		return freqH;

	// Calculate magnitude threshold
	float sum_of_magnitudes;
	sum_of_magnitudes = (std::accumulate(magnitudesH.begin(), magnitudesH.end(), 0)) + (std::accumulate(magnitudesL.begin(), magnitudesL.end(), 0));


	if ((magnitudesL[indexL] > (sum_of_magnitudes / 4)) || (magnitudesH[indexH - 4] > (sum_of_magnitudes / 4)))
	{
		if (magnitudesL[indexL] > magnitudesH[indexH - 4])
		{
			if ((magnitudesL[indexL] > (sum_of_magnitudes / 4)) && (magnitudesH[indexH - 4] > (magnitudesL[indexL] / 2)))
			{
				std::cout << "found";
			}
		}

		else
		{
			if (magnitudesL[indexL] < magnitudesH[indexH - 4])
			{
				if ((magnitudesH[indexH - 4] > (sum_of_magnitudes / 4)) && ((magnitudesH[indexH - 4] / 2) < magnitudesL[indexL]))
				{
					std::cout << "found";
				}
			}
		}
	}
	else {
		std::cout << "none";
	}

}

float ProcessData::goertzel(int sampleCount, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, std::vector<float>& recording)
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
		q0 = coeff * q1 - q2 + recording[i];
		q2 = q1;
		q1 = q0;
	}
	magnitude = sqrtf(pow(q1, 2) + pow(q2, 2) - q1 * q2 * coeff);
	return magnitude;
}
