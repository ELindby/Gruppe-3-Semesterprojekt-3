#include "package_collector.h"
#include "frame.h"
#include "SoundGenerator.h"

PackageCollector::PackageCollector() {}
PackageCollector::~PackageCollector() {}

std::vector<std::bitset<8>> PackageCollector::packageContainer;

void PackageCollector::AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram) {

	//Se først om pakken "består crc"
	if (!crc)
	{
		return;
	}

	//Se om pakken er en dublet
	if (dc)
	{
		SendACK();
		return;
	}

	//Send ikke ACK til ack
	if (!DeFrame::ack)
	{
		SendACK();	//Kalder funktion fra fysisk lag til at sende et ACK
		std::cout << "sender ack" << std::endl;
	}

	//Tilføj til packageContainer hvis ingen fejl og ikke dublet
	for (size_t i = 0; i < dataSize; i++)
	{
		PackageCollector::packageContainer.push_back(datagram[i]);
	}

	//Se om pakken er den sidste i beskeden
	if (spFlag)
	{
		//MessageToApp(); //Kalder funktion fra applikations laget til at display beskeden
		for (size_t i = 0; i < packageContainer.size(); i++)
		{
			std::cout << packageContainer[i];
		}
		std::cout << std::endl;
		PackageCollector::packageContainer = {}; //Tøm packageContainer til ny besked
	}
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