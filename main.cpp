#include "frame.h"
#include "deframe.h"

#include <iostream>

int main() {
	Frame framer;
	DeFrame deframer;

	std::vector<std::bitset<8>> lol;

	char besked[] = "Hej";
	std::vector<std::bitset<8>> msg = { 0b10101010, 0b10101111, 0b11110110 };

	std::cout << std::endl;
	framer.MessageCutter(msg);
	framer.PrintMsgSliced();

	//std::cout << "DEFRAMED:" << std::endl;

	deframer.UnPack(framer.GetPackages()[0]);

	//for (size_t i = 0; i < deframer.getDatagram().size(); i++)
	//{
	//	std::cout << deframer.getDatagram()[i] << ",";
	//}
	//std::cout << std::endl;
	std::cout << std::endl <<  "CRC CHECK: " << deframer.CrcCheck() << std::endl;

	system("pause");
	return 0;
}