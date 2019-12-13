#include "Recorder.h"
#include "GUI.h"

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

	// Create the recorder
	DTMFRecorder recorder;

	// Start recorder
	recorder.start(8000); // Argument (8000) = samplerate

	while (DTMFRecorder::static_syncing) //Åben først GUI når recorder er i sync
	{
		//Wait
	}

	//Setup GUI thread
	GUI gui_thread;
	sf::Thread thread(&GUI::setupGUI, &gui_thread);
	thread.launch();

	//Keep program from closing
	system("PAUSE");

	return 0;
}