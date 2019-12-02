#include "package_collector.h"

PackageCollector::PackageCollector() {}
PackageCollector::~PackageCollector() {}

void PackageCollector::AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram) {

	//Se f�rst om pakken "best�r crc"
	if (!crc)
	{
		return;
	}

	//Se om pakken er en dublet
	if (dc)
	{
		return;
	}

	//SendACK(); //Kalder funktion fra fysisk lag til at sende et ACK

	//Tilf�j til packageContainer hvis ingen fejl og ikke dublet
	for (size_t i = 0; i < dataSize; i++)
	{
		packageContainer.push_back(datagram[i]);
	}

	//Se om pakken er den sidste i beskeden
	//if (spFlag)
	//{
	//	//MessageToApp(); //Kalder funktion fra applikations laget til at display beskeden
	//	packageContainer = {}; //T�m packageContainer til ny besked
	//}
	return;
}