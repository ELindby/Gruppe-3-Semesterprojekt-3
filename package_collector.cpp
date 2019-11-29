#include "package_collector.h"

PackageCollector::PackageCollector(){}
PackageCollector::~PackageCollector(){}
DeFrame deframer;

void PackageCollector::AddToCollector() {
	std::vector<std::bitset<8>> datagram = deframer.getDatagram();

	//Se f�rst om pakken "best�r crc"
	if (!deframer.CrcCheck())
	{
		return;
	}

	//Se om pakken er en dublet
	if (deframer.DoubletCheck())
	{
		return;
	}

	//SendACK(); //Kalder funktion fra fysisk lag til at sende et ACK

	//Tilf�j til packageContainer hvis ingen fejl og ikke dublet
	for (size_t i = 0; i < datagram.size(); i++)
	{
		packageContainer.push_back(datagram[0]);
	}

	//Se om pakken er den sidste i beskeden
	if (deframer.getSpFlag())
	{
		//!MessageToApp(); //Kalder funktion fra applikations laget til at display beskeden
		packageContainer = {}; //T�m packageContainer til ny besked
	}
	return;
}