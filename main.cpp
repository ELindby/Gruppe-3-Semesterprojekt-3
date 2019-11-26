#include "frame.h"
#include "deframe.h"

#include <iostream>

int main() {
	Frame framer;
	DeFrame deframer;

	std::vector<std::bitset<8>> lol;

	char besked[] = "H";

	std::cout << std::endl;
	framer.MessageCutter(besked);
	framer.PrintMsgSliced();

	//std::cout << "DEFRAMED:" << std::endl;

	deframer.UnPack(framer.GetPackages()[0]);

	//for (size_t i = 0; i < deframer.getDatagram().size(); i++)
	//{
	//	std::cout << deframer.getDatagram()[i] << ",";
	//}
	//std::cout << std::endl;
	//std::cout << deframer.trailer;
	std::cout << std::endl <<  "CRC CHECK: " << deframer.crcCheck() << std::endl;

	system("pause");
	return 0;
}