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
	const sf::SoundBuffer& bufferR = recorder.getBuffer();
	sf::Sound sound(bufferR);
	//sound.setLoop(true);
	//sound.play();
	//// Play tone for some time
	//sf::sleep(sf::milliseconds(1000));


	// Generating sound
	float H = 1209, L = 941;

	const unsigned SAMPLES = 44100;
	const unsigned SAMPLE_RATE = 44100; // number of samples processed in 1 sec (time domain)
	const unsigned AMPLITUDE = 30000;
	sf::Int16 raw[SAMPLES];

	const double hz1336 = H / SAMPLE_RATE; // frequency
	double x = 0;
	for (unsigned i = 0; i < SAMPLES; i++) {
		raw[i] = AMPLITUDE * sin(x * TWO_PI);
		x += hz1336;
	}
	const double hz770 = L / SAMPLE_RATE;  // frequency
	double y = 0;
	for (unsigned i = 0; i < SAMPLES; i++) {
		raw[i] = (raw[i] + (AMPLITUDE * sin(y * TWO_PI))) / 2;
		y += hz770;
	}
	sf::SoundBuffer bufferG;
	if (!bufferG.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
	}


	// finding the highest frequencies
	HigestFreq(bufferR);
	std::cout << '\n' << "Highest: " << highL << " & " << highH << std::endl;

	system("pause");
}

receive::~receive(){}

void receive::HigestFreq(const sf::SoundBuffer buffer)
{
	const sf::Int16* samples = buffer.getSamples();
	std::size_t sampleSize = buffer.getSampleCount();
	unsigned int sampleRate = buffer.getSampleRate();

	// For test
	//std::cout << sampleRate << '\n' << sampleSize << '\n' << std::endl;

	// Detect two higest frequencies
	std::vector<float> magnitudesL, magnitudesH;

	for (int a = 0; a < 4; a++) {
		magnitudesL.push_back(Goertzel(sampleSize, DTMFtones[a], sampleRate, samples));
		std::cout << DTMFtones[a] << ":  " << magnitudesL.at(a) << std::endl;

		magnitudesH.push_back(Goertzel(sampleSize, DTMFtones[a + 4], sampleRate, samples));
		std::cout << DTMFtones[a + 4] << ": " << magnitudesH.at(a) << std::endl;
	}
	float maxL = 0, maxH = 0;
	int indexL, indexH;
	for (unsigned int i = 0; i < 4; i++) {
		if (magnitudesL[i] > maxL) {
			maxL = magnitudesL[i];
			indexL = i;
		}
		if (magnitudesH[i] > maxH) {
			maxH = magnitudesH[i];
			indexH = i + 4;
		}
	}
	highL = DTMFtones[indexL];
	highH = DTMFtones[indexH];
}

float receive::Goertzel(std::size_t numSamples, unsigned int targetFrequency, unsigned int sampleRate, const sf::Int16* data) {

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
}