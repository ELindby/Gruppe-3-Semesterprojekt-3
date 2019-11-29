#include "send.h"
#include "receive.h"
#include "Recorder.h"
#include "SoundGenerator.h"

#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <thread>



int main() {


	// Check that audio is available
	if (!sf::SoundRecorder::isAvailable())
	{
		std::cout << "Audio capture not available" << std::endl;
	}

	// create the recorder
	DTMFRecorder recorder;

	// Start recorder
	recorder.start(8000); // argument = samplerate

	// Message input
	std::string input;
	getline(std::cin, input);

	SoundGenerator message(input);

	//Keep program from closing
	Sleep(100000);

	return 0;
}