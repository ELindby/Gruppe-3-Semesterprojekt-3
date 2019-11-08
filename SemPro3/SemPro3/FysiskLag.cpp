#include "FysiskLag.h"

FysiskLag::FysiskLag() {}
FysiskLag::~FysiskLag() {}

FysiskLag::FysiskLag(char input) {
	DTMFConverter(input);
	ToneGenerator();
}

