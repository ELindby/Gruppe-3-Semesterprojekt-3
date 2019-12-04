#include "package_collector.h"
#include "frame.h"
#include "SoundGenerator.h"

PackageCollector::PackageCollector() {}
PackageCollector::~PackageCollector() {}

std::vector<std::bitset<8>> PackageCollector::packageContainer;
//bool PackageCollector::static_spFlag;


void PackageCollector::AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram) {

	static_spFlag = spFlag; //Dette flag skal bruges af GetMsg()

	//Se først om pakken "består crc"
	if (!crc)
	{
		return;
	}

	//Send ikke ACK til ack
	if (!DeFrame::ack)
	{
		return;
	}


	//Se om pakken er en dublet
	if (dc)
	{
		SendACK();
		return;
	}

	SendACK();

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

std::vector<std::bitset<8>> PackageCollector::GetMsg() {
	if (!static_spFlag)
	{
		return std::vector<std::bitset<8>>{}; //Return tom vektor hvis funktionen kaldes og sidste pakke i beskeden ikke er der.
	}
	return packageContainer;
}