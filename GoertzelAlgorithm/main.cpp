//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <fstream>
//
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Work!");
//
//
//	// first check if an input audio device is available on the system
//	if (!sf::SoundBufferRecorder::isAvailable())
//	{
//		// error: audio capture is not available on this system
//		std::cout << "ERROR: No recording device found!" << '\n';
//	}
//
//	// create the recorder
//	sf::SoundBufferRecorder recorder;
//
//	sf::SoundBuffer buffer;
//	sf::Sound sound;
//
//	while (window.isOpen())
//	{
//		sf::Event Event;
//		while (window.pollEvent(Event))
//		{
//			switch (Event.type)
//			{
//			case sf::Event::Closed:
//				//// stop the capture
//				//recorder.stop();
//
//				//// retrieve the buffer that contains the captured audio data
//				//const sf::SoundBuffer& buffer = recorder.getBuffer();
//
//				//buffer.saveToFile("recording.ogg");
//
//				window.close();
//				break;
//
//			case sf::Event::KeyPressed:
//				if (Event.key.code == sf::Keyboard::R)
//				{
//					// start recording
//					recorder.start();
//				}
//				else if (Event.key.code == sf::Keyboard::S)
//				{
//					// Stop recording
//					recorder.stop();
//
//					// Set up sound buffer
//					buffer = recorder.getBuffer();
//					sound.setBuffer(buffer);
//
//					// Sample audio
//					const sf::Int16* samples = buffer.getSamples();
//					std::size_t count = buffer.getSampleCount();
//					std::cout << count << '\n';
//
//					std::ofstream outfile;
//					outfile.open("GoertzelTest.csv");
//					for (size_t i = 0; i < count; i++)
//					{
//						outfile << i << ";";
//						outfile << samples[i] << std::endl;
//					}
//					outfile.close();
//
//
//					//// Play recording
//					//sound.play();
//				}
//			}
//		}
//
//		//Choose color of display Window
//		//window.clear(sf::Color(0, 240, 255));
//		//window.display();
//
//	}
//	return 0;
//}








//// Test load sound
//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <fstream>
//
//
//int main()
//{
//	
//
//
//	sf::SoundBuffer buffer;
//	if (!buffer.loadFromFile("dtmfTest.wav"))
//	{
//		// Should trow error
//		std::cout << "Sound FaiL!" << '\n';
//	}
//
//	sf::Sound sound;
//	sound.setBuffer(buffer);
//	sound.setLoop(true);
//	sound.play();
//
//	sf::sleep(sf::milliseconds(100));
//
//	return 0;
//}







// Samples all 16 DTMF tones into .csv file with sample number 
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>



int lowDTMFFreq(char DTMFchar)
{
	int lowDTMFFreq;

	switch (DTMFchar)
	{
	case '1': case '2': case '3': case 'A': lowDTMFFreq = 697; break;
	case '4': case '5': case '6': case 'B': lowDTMFFreq = 770; break;
	case '7': case '8': case '9': case 'C': lowDTMFFreq = 852; break;
	case '*': case '0': case '#': case 'D': lowDTMFFreq = 941; break;
	}

	return lowDTMFFreq;
}


int highDTMFFreq(char DTMFchar)
{
	int highDTMFFreq;

	switch (DTMFchar)
	{
	case '1': case '4': case '7': case '*': highDTMFFreq = 1209; break;
	case '2': case '5': case '8': case '0': highDTMFFreq = 1336; break;
	case '3': case '6': case '9': case '#': highDTMFFreq = 1477; break;
	case 'A': case 'B': case 'C': case 'D': highDTMFFreq = 1633; break;
	}

	return highDTMFFreq;
}



void sampleDTMFsignal(char DTMFchar, const int wSampleRate, const int nSamples)
{
	// Get high and low frequency of DTMF tone
	int lowFreq = lowDTMFFreq(DTMFchar);
	int highFreq = highDTMFFreq(DTMFchar);

	// Generate samples of DTMF tone signal
	const double twoPi = 6.28318;
	double piPoduct1 = (twoPi * lowFreq) / wSampleRate;
	double piPoduct2 = (twoPi * highFreq) / wSampleRate;

	std::vector<int> DTMFtone;

	for (unsigned i = 0; i < nSamples; i++)
	{
		DTMFtone.push_back(128 * (63 * sin(i * piPoduct1) + 63 * sin(i * piPoduct2)));
		//DTMFtone[i] = 128 * (63 * sin(i * piPoduct1) + 63 * sin(i * piPoduct2));
	}


	// Set Sample text
	std::string fileName;
	switch (DTMFchar)
	{
	case '1': fileName = "sample_1.csv"; break;
	case '2': fileName = "sample_2.csv"; break;
	case '3': fileName = "sample_3.csv"; break;
	case '4': fileName = "sample_4.csv"; break;
	case '5': fileName = "sample_5.csv"; break;
	case '6': fileName = "sample_6.csv"; break;
	case '7': fileName = "sample_7.csv"; break;
	case '8': fileName = "sample_8.csv"; break;
	case '9': fileName = "sample_9.csv"; break;
	case '0': fileName = "sample_0.csv"; break;
	case 'A': fileName = "sample_A.csv"; break;
	case 'B': fileName = "sample_B.csv"; break;
	case 'C': fileName = "sample_C.csv"; break;
	case 'D': fileName = "sample_D.csv"; break;
	case '*': fileName = "sample_stjerne.csv"; break;
	case '#': fileName = "sample_#.csv"; break;
	default:
		break;
	}



	// Create file with samples
	std::ofstream outfile;
	outfile.open(fileName);
	for (size_t i = 0; i < nSamples; i++)
	{
		//std::cout << DTMFtone[i] << '\t';
		outfile << i + 1 << ";";
		outfile << DTMFtone[i] << std::endl;
	}
	outfile.close();
}



int main()
{
	// Make samples of all DTMF tones:

	// Sample setup:
	// 8 kHz sample rate 8 bit data
	const int wSampleRate = 8000;  //giver fornuftig graf ved 1 - hvorfor?
	const int nSamples = 8000;

	// Sample all 16 DTMF tones in .csv file
	std::vector<char> chars = {'1','2','3','4','5','6','7','8','9','0','A','B','C','D','*','#' };
	for (size_t i = 0; i < chars.size(); ++i)
	{
		sampleDTMFsignal(chars[i], wSampleRate, nSamples);
	}

	return 0;
}