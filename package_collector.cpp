#include "package_collector.h"
#include "frame.h"
#include "SoundGenerator.h"

PackageCollector::PackageCollector() {}
PackageCollector::~PackageCollector() {}

std::vector<std::bitset<8>> PackageCollector::packageContainer;

void PackageCollector::AddToCollector(bool crc, bool dc, int dataSize, bool spFlag, std::vector<std::bitset<8>> datagram) {
	std::cout << "spFlag" << spFlag << std::endl;

	//Check if package passes CRC
	if (!crc)
	{
		std::cout << "CRC FEJL" << std::endl;
		return;
	}

	//Dont reply ACK to an ACK message
	if (DeFrame::ack)
	{
		std::cout << "Recieved ACK " << spFlag << std::endl;
		return;
	}

	std::cout << "spFlag: " << spFlag << std::endl;

	//Check if package is a dublet
	if (dc)
	{
		std::cout << "Dublet recieved" << std::endl;
		SendACK();
		return;
	}

	SendACK();

	//Add to packageContainer if no errors, and message isnt a dublet
	for (size_t i = 0; i < dataSize; i++)
	{
		PackageCollector::packageContainer.push_back(datagram[i]);
	}

	//If last package in a transmission
	if (spFlag)
	{
		for (size_t i = 0; i < packageContainer.size(); i++)
		{
			std::cout << packageContainer[i];
		}
		std::cout << std::endl;

		static_spFlag = spFlag; //Set public sp flag so Application layer knows a complete transmission has been recieved and a message is ready to be displayed
	}
	return;
}

void PackageCollector::SendACK() { //Send acknowledge package

	std::cout << "Sending ack" << std::endl;

	DTMFRecorder::pauseRecording = true; //Stop listening, Half Duplex

	Frame framer;
	SoundGenerator sg;

	framer.MessageCutter(std::vector<std::bitset<8>>{}); //Create ACK package

	sg.convertToDTMF(framer.GetPackages()[0]);

	DTMFRecorder::pauseRecording = false; //Start listening again
}

std::vector<std::bitset<8>> PackageCollector::GetMsg() {
	return packageContainer;
}

void PackageCollector::clearContainer() {
	packageContainer = {};
}