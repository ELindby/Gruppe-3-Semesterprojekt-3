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

//void convertFromDTMF(std::vector<int>recordedMessage)
//{
//	// Combine two frequencies to a single character
//	std::vector<char> unwrappedMessage;
//
//	std::cout << "size:" << recordedMessage.size() << std::endl;
//
//	//for (int i = 0; i < (recordedMessage.size()); i++)
//	//{
//	//	std::cout << recordedMessage[i] << std::endl;;
//	//}
//
//	for (int i = 0; i < (recordedMessage.size() / 4); i++)
//	{
//		int binaryValue = 0b00000000;
//
//		// std::cout << "tjek:" << recordedMessage[i * 4] << std::endl << recordedMessage[i * 4 +1] << std::endl << recordedMessage[i * 4+2] << std::endl << recordedMessage[i * 4+3] << std::endl;
//
//		switch (recordedMessage[i*4])
//		{
//		case 697:
//			binaryValue = 0b00000000;
//			break;
//		case 770:
//			binaryValue = 0b00000100;
//			break;
//		case 852:
//			binaryValue = 0b00001000;
//			break;
//		case 941:
//			binaryValue = 0b00001100;
//			break;
//		}
//
//		switch (recordedMessage[i*4+1])
//		{
//		case 1209:
//			binaryValue |= 0b00000000;
//			break;
//		case 1336:
//			binaryValue |= 0b00000001;
//			break;
//		case 1477:
//			binaryValue |= 0b00000010;
//			break;
//		case 1633:
//			binaryValue |= 0b00000011;
//			break;
//		}
//
//		switch (recordedMessage[i*4+2])
//		{
//		case 697:
//			binaryValue |= 0b00000000;
//			break;
//		case 770:
//			binaryValue |= 0b01000000;
//			break;
//		case 852:
//			binaryValue |= 0b10000000;
//			break;
//		case 941:
//			binaryValue |= 0b11000000;
//			break;
//		}
//
//		switch (recordedMessage[i*4+3])
//		{
//		case 1209:
//			binaryValue |= 0b00000000;
//			break;
//		case 1336:
//			binaryValue |= 0b00010000;
//			break;
//		case 1477:
//			binaryValue |= 0b00100000;
//			break;
//		case 1633:
//			binaryValue |= 0b00110000;
//			break;
//		}
//
//		char asChar = binaryValue;
//
//		std::cout << binaryValue << " " << asChar << std::endl;
//
//		unwrappedMessage.push_back(asChar);
//	}
//
//	//for (int i = 0; i < unwrappedMessage.size(); i++)
//	//{
//	//	std::cout << unwrappedMessage[i];
//	//}
//
//}

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

	////test
	//std::vector<int> testMessage;

	//testMessage.push_back(852);
	//testMessage.push_back(1209);
	//testMessage.push_back(770);
	//testMessage.push_back(1209); //H

	//testMessage.push_back(770);
	//testMessage.push_back(1336);
	//testMessage.push_back(770);
	//testMessage.push_back(1209); //E 

	//testMessage.push_back(852);
	//testMessage.push_back(1477);
	//testMessage.push_back(770);
	//testMessage.push_back(1209); //J

	//convertFromDTMF(testMessage);

	// Message input
	std::string input;
	getline(std::cin, input);

	SoundGenerator message(input);

	//Keep program from closing
	Sleep(100000);

	return 0;
}