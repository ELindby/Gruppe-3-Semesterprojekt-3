#include "frame.h"
#include "deframe.h"

#include <iostream>

int main() {
	Frame framer;
	DeFrame deframer;

	char besked[] = "hasdasdsdfsdfsdgsdgsdgsdgdfgdfgdf dg  rth h rh rrt ert er ert ert ete rtert er hvad fanden er det der forgår her hvorfor kommer jeg ikke med?";
	std::string unpackedBesked;

	std::cout << std::endl;
	framer.MessageCutter(besked);
	framer.PrintMsgSliced();

	unpackedBesked = deframer.UnPack(framer.GetPackages()[0]) + "|" + deframer.UnPack(framer.GetPackages()[1]) + "|" + deframer.UnPack(framer.GetPackages()[2]) + "|" + deframer.UnPack(framer.GetPackages()[3]);

	std::cout << unpackedBesked << std::endl;

	system("pause");
	return 0;
}