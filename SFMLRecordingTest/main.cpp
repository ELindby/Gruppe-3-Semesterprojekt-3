//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//
//int main() 
//{
//	sf::RenderWindow window(sf::VideoMode(600,600),"SFML Work!");
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
//	// start the capture
//	recorder.start();
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				// stop the capture
//				recorder.stop();
//
//				// retrieve the buffer that contains the captured audio data
//				const sf::SoundBuffer& buffer = recorder.getBuffer();
//
//				buffer.saveToFile("recording.ogg");
//
//				window.close();
//
//				break;
//			}
//		}
//
//	}


	//// wait...
	//sf::SoundBuffer recordingBuffer;


	//sf::Sound sound(buffer);
	//sound.play();
//}


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Work!");


	// first check if an input audio device is available on the system
	if (!sf::SoundBufferRecorder::isAvailable())
	{
		// error: audio capture is not available on this system
		std::cout << "ERROR: No recording device found!" << '\n';
	}

	// create the recorder
	sf::SoundBufferRecorder recorder;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				//// stop the capture
				//recorder.stop();

				//// retrieve the buffer that contains the captured audio data
				//const sf::SoundBuffer& buffer = recorder.getBuffer();

				//buffer.saveToFile("recording.ogg");

				window.close();
				break;

			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::R)
				{
					// start recording
					recorder.start();
				}
				else if (Event.key.code == sf::Keyboard::S)
				{
					// Stop recording
					recorder.stop();

					// Set up sound buffer
					buffer = recorder.getBuffer();
					sound.setBuffer(buffer);

					// Sample audio
					const sf::Int16* samples = buffer.getSamples();
					std::size_t count = buffer.getSampleCount();
					std::cout << count << '\n';

						std::ofstream outfile;
						outfile.open("Sample_3.csv");
					for (size_t i = 0; i < count; i++)
					{
						outfile << i << ";";
						outfile << samples[i] << std::endl;
					}
						outfile.close();


					//// Play recording
					//sound.play();
				}
			}
		}

		//Choose color of display Window
		//window.clear(sf::Color(0, 240, 255));
		//window.display();
		
	}
	return 0;
}