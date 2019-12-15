#include "deframe.h"
#include "package_collector.h"

DeFrame::DeFrame() {};
DeFrame::~DeFrame() {};

bool DeFrame::ack = false;
PackageCollector packageCollector;

//Hi is Header information
void DeFrame::Hi(std::bitset<8> HeaderByte) { //Set member variables from information in header of recieved message
	std::bitset<8> header = HeaderByte;

	// Find DataSize (length of payload)
	std::bitset<8> bit_DataSize;
	bit_DataSize = header & std::bitset<8>(0b00011111);

	dataSize = (int)(bit_DataSize.to_ulong());

	//Determine if message is an acknowledge
	if (dataSize == 0)
	{
		ack = true;
	}
	else
	{
		ack = false;
	}

	//LAST PACKAGE
	sp = header[6]; //x[1]xxxxxx

	//Sequence number
	sq = header[7]; //[1]
}

void DeFrame::UnPack(std::vector<std::bitset<8>> package) {
	// Check for errors - dont save information if packets are discarded
	if (package.size() < 2)
	{
		std::cout << "Length of data too short, package discarded." << std::endl;
		return;
	}

	std::bitset<8> bit_DataSize = package[0] & std::bitset<8>(0b00011111);


	int tempdataSize = (int)(bit_DataSize.to_ulong());
	if (tempdataSize != (package.size() - 2)) //If some data was lost
	{
		std::cout << "Length of data recieved is not equal to length in header." << std::endl;
		return;
	}

	oldsq = sq; //Update old sq flag (Sequence number)

	//Get Header Information
	Hi(package[0]); //Get header information from package
	header = package[0]; //save header
	trailer = package[dataSize + 1]; //save trailer
	bool crcCheck;
	bool dubletCheck;

	//Clear datagram
	datagram = {};

	//Get datagram (Package payload)
	std::bitset<8> workingByte;
	for (size_t i = 1; i <= dataSize; i++)
	{
		workingByte = package[i];
		datagram.push_back(workingByte);
	}

	//Add to Package Collector
	crcCheck = CrcCheck();
	if (!crcCheck) {
		std::cout << "CRC caught an error and discarded the package\n";
		sq = oldsq;
		sp = false; //if package is discarded, sp (which was of last package) will always be 0, as a new package should always be recieved afterwards.
		return;
	}
	dubletCheck = DoubletCheck();
	packageCollector.AddToCollector(crcCheck, dubletCheck, dataSize, sp, datagram);

	//Reset oldsq if transmission is over
	if (sp == true)
	{
		oldsq = 0;
	}
}

std::vector<std::bitset<8>> DeFrame::getDatagram() //Getter for datagram (Payload)
{
	return datagram;
}

bool DeFrame::CrcCheck() { //Check CRC for package
	std::vector<int> vecIntToCrcCheck = {};
	bool check;

	for (size_t i = 0; i < 8; i++)
	{
		vecIntToCrcCheck.push_back(header[7 - i]);
	}

	if (0 <= dataSize)
	{
		for (size_t i = 0; i < dataSize; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				vecIntToCrcCheck.push_back(datagram[i][7 - j]);
			}
		}
	}

	for (size_t i = 0; i < 7; i++)
	{
		vecIntToCrcCheck.push_back(trailer[6 - i]);
	}

	check = crcClass.receiverCheck(vecIntToCrcCheck);
	return check;
}

bool DeFrame::getAckFlag() {
	return ack;
}

bool DeFrame::getSpFlag() {
	return sp;
}

bool DeFrame::DoubletCheck() {
	if (oldsq != sq)
	{
		return false;
	}
	else
	{
		return true;
	}
}
