#include "receive.h"

receive::receive(){
	//assert(sf::SoundBufferRecorder::isAvailable());

	//// Recording sound
	//sf::SoundBufferRecorder recorder;
	//recorder.start();
	//std::cout << "Recording" << std::endl;
	//Sleep(1000);
	//recorder.stop();
	//std::cout << "Recording stopped" << std::endl;

	//// Playing recorded sound
	//const sf::SoundBuffer& buffer = recorder.getBuffer();
	//sf::Sound sound(buffer);
	//sound.play();

	//// Gathering and displaying information - samples, sample rate and block size
	//const sf::Int16* samples = buffer.getSamples();
	//std::size_t sampleSize = buffer.getSampleCount();
	//unsigned int sampleRate = buffer.getSampleRate();

	//float DetectedFreq = goertzel(sampleSize, 400, sampleRate, samples);

	//// For test
	//std::cout << sampleRate << '\n' << sampleSize << '\n' << DetectedFreq << std::endl;


	const unsigned SAMPLES = 44100;
	const unsigned SAMPLE_RATE = 44100; // number of samples processed in 1 sec (time domain)
										// numbers should match
	const unsigned AMPLITUDE = 30000;

	sf::Int16 raw[SAMPLES];

	const double hz1336 = 1336. / SAMPLE_RATE; // Frequency
	double x = 0;
	for (unsigned i = 0; i < SAMPLES; i++) {
		raw[i] = AMPLITUDE * sin(x * TWO_PI);
		x += hz1336;
	}

	const double hz770 = 770. / SAMPLE_RATE;
	double y = 0;
	for (unsigned i = 0; i < SAMPLES; i++) {
		raw[i] = (raw[i] + (AMPLITUDE * sin(y * TWO_PI))) / 2;
		y += hz770;
	}

	sf::SoundBuffer buffer;		// SoundBuffer class contains sound
	if (!buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {	// mono
		std::cerr << "Loading failed!" << std::endl;
	}

	//// Playing recorded sound
	//sf::Sound sound(buffer);
	//sound.play();

	const sf::Int16* samples = buffer.getSamples();
	std::size_t sampleSize = buffer.getSampleCount();
	unsigned int sampleRate = buffer.getSampleRate();

	// For test
	std::cout << sampleRate << '\n' << sampleSize << '\n' << std::endl;

	float DetectedFreq1 = goertzel(sampleSize, 697, sampleRate, samples);
	float DetectedFreq2 = goertzel(sampleSize, 770, sampleRate, samples);
	float DetectedFreq3 = goertzel(sampleSize, 852, sampleRate, samples);
	float DetectedFreq4 = goertzel(sampleSize, 941, sampleRate, samples);
	float DetectedFreq5 = goertzel(sampleSize, 1209, sampleRate, samples);
	float DetectedFreq6 = goertzel(sampleSize, 1336, sampleRate, samples);
	float DetectedFreq7 = goertzel(sampleSize, 1477, sampleRate, samples);
	float DetectedFreq8 = goertzel(sampleSize, 1633, sampleRate, samples);
	
	std::cout << std::setprecision(15) << "697:  " << DetectedFreq1 << std::endl;
	std::cout << std::setprecision(15) << "770:  " << DetectedFreq2 << std::endl;
	std::cout << std::setprecision(15) << "852:  " << DetectedFreq3 << std::endl;
	std::cout << std::setprecision(15) << "941:  " << DetectedFreq4 << std::endl;
	std::cout << std::setprecision(15) << "1209: " << DetectedFreq5 << std::endl;
	std::cout << std::setprecision(15) << "1336: " << DetectedFreq6 << std::endl;
	std::cout << std::setprecision(15) << "1477: " << DetectedFreq7 << std::endl;
	std::cout << std::setprecision(15) << "1633: " << DetectedFreq8 << std::endl;



	//std::vector<float> magnitudes;

	//for (int a = 1; a < 2000; a++)
	//{
	//	magnitudes.push_back(goertzel(sampleSize, a, sampleRate, samples));

	//	std::cout << a << ":" << magnitudes.at(a - 1) << std::endl;
	//}

	//float max = *max_element(magnitudes.begin(), magnitudes.end());

	//std::cout << "Highest amplitude: " << std::distance(magnitudes.begin(), max_element(magnitudes.begin(), magnitudes.end())) + 1 << "Hz : " << max << std::endl;

	////sort(magnitudes.begin(), magnitudes.end(), [](float x, float y) {return x > y; });

	////std::cout << magnitudes.at(1);





	system("pause");
}
receive::~receive(){}

float receive::goertzel(std::size_t numSamples, unsigned int targetFrequency, unsigned int sampleRate, const sf::Int16* data) {

	int     k, i;
	float   floatnumSamples;
	float   omega, cosine, coeff, q0, q1, q2, magnitude;

	floatnumSamples = (float)numSamples;
	k = (int)(0.5 + ((floatnumSamples * targetFrequency) / sampleRate));
	omega = (2.0 * PI * k) / floatnumSamples;
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