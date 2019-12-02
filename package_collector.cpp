#include "package_collector.h"

#include "deframe.h"
#include "frame.h"
#include "SoundGenerator.h"

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

	//Kalder funktion fra fysisk lag til at sende et ACK

	sf::sleep(sf::milliseconds(1000)); // wait for sender to be ready
	std::cout << "sender ack" << std::endl;

	SendACK();

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

void PackageCollector::SendACK() {
	DTMFRecorder::pauseRecording = true; // stop med at lytte

	Frame framer;
	SoundGenerator sg;

	framer.MessageCutter(std::vector<std::bitset<8>>{}); //Lav ack pakke

	sg.convertToDTMF(framer.GetPackages()[0]);

	DTMFRecorder::pauseRecording = false; // start med at lytte
}