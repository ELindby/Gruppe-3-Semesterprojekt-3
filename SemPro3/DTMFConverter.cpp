#include "DTMFConverter.h"

DTMFConverter::DTMFConverter() {}
DTMFConverter::~DTMFConverter() {}

DTMFConverter::DTMFConverter(char input, int lowDTMFL, int lowDTMFU, int highDTMFL, int highDTMFU) {
	// Masks upper and lower nipple of ASCII byte
	char lowerNipple = 0b00001111 & input;
	char upperNipple = (0b11110000 & input) >> 4;

	// Finds DTMF tone for lower nipple
	lowDTMFL = LowToneFrequency(lowerNipple);
	highDTMFL = HighToneFrequency(lowerNipple);

	// Finds DTMF tone for upper nipple
	lowDTMFU = LowToneFrequency(upperNipple);
	highDTMFU = HighToneFrequency(upperNipple);

	// Displays information at terminal
	std::cout << input << ": " << '\n' << lowDTMFL << '\t' << highDTMFL << '\n';
	std::cout << lowDTMFU << '\t' << highDTMFU << std::endl;
}

int DTMFConverter::LowToneFrequency(char low) {
	assert(low < 16);
	int lowDTMF = 0;
	if (low < 12) {
		if (low < 8) {
			if (low < 4) {
				return lowDTMF = 697;
			}
			return lowDTMF = 770;
		}
		return lowDTMF = 852;
	}
	return lowDTMF = 941;
}
int DTMFConverter::HighToneFrequency(char high) {
	assert(high < 16);
	int highDTMF = 0;
	int col = (high + 1) % 4;

	switch (col) {
	case 1:
		return highDTMF = 1209;
	case 2:
		return highDTMF = 1336;
	case 3:
		return highDTMF = 1477;
	case 0:
		return highDTMF = 1633;
	}
}
