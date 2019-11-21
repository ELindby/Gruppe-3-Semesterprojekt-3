#include "frame.h"
#include "deframe.h"

#include <iostream>

int main() {
	Frame framer;
	DeFrame deframer;

	std::vector<std::bitset<8>> lol;

	char besked[] = "fdgdfgdfgdf g ddg dfgh fjf j edf xftu fhsgsb sysrbs ss4 6dr dr fghj qa";

	std::cout << std::endl;
	framer.MessageCutter(besked);
	framer.PrintMsgSliced();

	system("pause");
	return 0;
}