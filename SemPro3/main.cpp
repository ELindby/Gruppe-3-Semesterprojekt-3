#pragma once

#include "ApplicationLayer.h"
#include "DataLinkLayer.h"
#include "PhysicalLayer.h"
#include "Framer.h"
#include "CRC.h"

#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

int main() {
	Framer framer;
	//DeFrame deframer;

	std::vector<std::bitset<8>> message;

	char besked[] = "";
	for (size_t i = 0; i < strlen(besked); i++)
	{
		message.push_back(besked[i]);
	}
	 

	std::cout << std::endl;
	framer.MessageCutter(message);
	framer.PrintMsgSliced();

	//std::cout << "DEFRAMED:" << std::endl;

	//deframer.UnPack(framer.GetPackages()[0]);

	//for (size_t i = 0; i < deframer.getDatagram().size(); i++)
	//{
	//	std::cout << deframer.getDatagram()[i] << ",";
	//}
	//std::cout << std::endl;
	//std::cout << deframer.trailer;
	//std::cout << std::endl << "CRC CHECK: " << deframer.crcCheck() << std::endl;

	//std::string input;
	//getline(std::cin, input);
	//std::istringstream sstr(input);
	//char n;
	//std::vector<char> chars;
	//while (sstr >> std::noskipws >> n) {
	//	chars.push_back(n);
	//}
	//// Play entered chars as DTMF tones
	//for (size_t i = 0; i < chars.size(); i++) {
	//	PhysicalLayer message(chars[i]);
	//}
	system("pause");

	return 0;
}