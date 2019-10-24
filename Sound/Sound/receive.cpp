#include "receive.h"

receive::receive(){
	assert(sf::SoundBufferRecorder::isAvailable());

	// Recording sound
	sf::SoundBufferRecorder recorder;
	recorder.start();
	std::cout << "Recording" << std::endl;
	Sleep(1000);
	recorder.stop();
	std::cout << "Recording stopped" << std::endl;

	// Playing recorded sound
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	sf::Sound sound(buffer);
	sound.play();

	// Gathering and displaying information - samples, sample rate and block size
	const sf::Int16* samples = buffer.getSamples();
	std::size_t sampleSize = buffer.getSampleCount();
	unsigned int sampleRate = buffer.getSampleRate();

	float DetectedFreq = goertzel(sampleSize, 400, sampleRate, samples);

	// For test
	std::cout << sampleRate << '\n' << sampleSize << '\n' << DetectedFreq << std::endl;

	system("pause");
}
receive::~receive(){}

float receive::goertzel(std::size_t numSamples, unsigned int TARGET_FREQUENCY, unsigned int SAMPLING_RATE, const sf::Int16* data) {

	int     k, i;
	float   floatnumSamples;
	float   omega, sine, cosine, coeff, q0, q1, q2, magnitude;

	floatnumSamples = (float)numSamples;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i < numSamples; i++) {
		q0 = coeff * q1 - q2 + data[i];
		q2 = q1;
		q1 = q0;
	}
	magnitude = sqrtf(pow(q1, 2) + pow(q2, 2) - q1 * q2 * coeff);
	return magnitude;

	// Needs to return true or false, when threshold is determined.
}