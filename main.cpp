#include "send.h"
#include "receive.h"
#include "Recorder.h"

#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>
#include <iomanip>

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

	Sleep(10000);

	return 0;
}