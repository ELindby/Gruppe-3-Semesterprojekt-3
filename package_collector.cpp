#include "package_collector.h"
#include "frame.h"
#include "SoundGenerator.h"

PackageCollector::PackageCollector() {}
PackageCollector::~PackageCollector() {}

std::vector<std::bitset<8>> PackageCollector::packageContainer;
//bool PackageCollector::static_spFlag;


void PackageCollector::AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram) {

	//Se først om pakken "består crc"
	if (!crc)
	{
		std::cout << "CRC FEJL" <<std::endl;
		return;
	}

	//Send ikke ACK til ack
	if (DeFrame::ack)
	{
		std::cout << "modtog ack " << spFlag << std::endl;
		return;
	}

	// std::cout << "spFlag: " << spFlag << std::endl;

	//Se om pakken er en dublet
	if (dc)
	{
		std::cout << "Dublet modtaget" << std::endl;
		SendACK();
		return;
	}

	SendACK();

	//Tilføj til packageContainer hvis ingen fejl og ikke dublet
	for (size_t i = 0; i < dataSize; i++)
	{
		PackageCollector::packageContainer.push_back(datagram[i]);
	}

	//for (size_t i = 0; i < packageContainer.size(); i++)
	//{
	//	std::cout << packageContainer[i];
	//}

	//Se om pakken er den sidste i beskeden
	if (spFlag)
	{
		//MessageToApp(); //Kalder funktion fra applikations laget til at display beskeden
		for (size_t i = 0; i < packageContainer.size(); i++)
		{
			std::cout << packageContainer[i];
		}
		std::cout << std::endl;

		static_spFlag = spFlag; //Dette flag skal bruges af GetMsg()
	}
	return;
}

void PackageCollector::SendACK() {

	std::cout << "Sender ack" << std::endl;

	DTMFRecorder::pauseRecording = true; // stop med at lytte

	Frame framer;
	SoundGenerator sg;

	framer.MessageCutter(std::vector<std::bitset<8>>{}); //Lav ack pakke

	sg.convertToDTMF(framer.GetPackages()[0]);

	DTMFRecorder::pauseRecording = false; // start med at lytte
}

std::vector<std::bitset<8>> PackageCollector::GetMsg() {
	return packageContainer;
}

void PackageCollector::clearContainer() {
	packageContainer = {};
}