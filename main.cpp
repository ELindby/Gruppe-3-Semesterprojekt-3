#include "send.h"
#include "receive.h"
#include "Recorder.h"
#include "SoundGenerator.h"
#include "package_sender.h"
#include "deframe.h"

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

	//convert to bitset
	std::vector<std::bitset<8>> msg;

	for (int i = 0; i < input.length(); i++)
	{
		msg.push_back(std::bitset<8>(input[i]));
	}

	//SoundGenerator generator;
	//generator.convertToDTMF(msg);

	PackageSender sender;
	sender.SendMessage(msg);

	// std::vector<std::bitset<8>> msg = { 0b00110011, 0b00110011 };

	// PackageSender sender;
	// sender.SendMessage(msg);





	//Keep program from closing
	Sleep(100000);

	return 0;
}