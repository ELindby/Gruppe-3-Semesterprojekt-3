#pragma once

#include "ApplicationLayer.h"
#include "DataLinkLayer.h"
#include "PhysicalLayer.h"

#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

int main() {

	std::string input;
	getline(std::cin, input);
	std::istringstream sstr(input);
	char n;
	std::vector<char> chars;
	while (sstr >> std::noskipws >> n) {
		chars.push_back(n);
	}
	// Play entered chars as DTMF tones
	for (size_t i = 0; i < chars.size(); i++) {
		PhysicalLayer message(chars[i]);
	}
	system("pause");

	return 0;
}