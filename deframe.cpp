#include "deframe.h"
#include "package_collector.h"

DeFrame::DeFrame() {};
DeFrame::~DeFrame() {};

bool DeFrame::ack = false;
PackageCollector packageCollector;

//Hi er Header information
void DeFrame::Hi(std::bitset<8> package) {
	std::bitset<8> header = package;

	//________________DATA SIZE
	std::bitset<8> bit_DataSize;
	bit_DataSize = header & std::bitset<8>(0b00011111);

	dataSize = (int)(bit_DataSize.to_ulong());

	//________________ACK
	if (dataSize == 0)
	{
		ack = true;
	}
	else
	{
		ack = false;
	}

	//________________LAST PACKAGE
	sp = header[6]; //x[1]xxxxxx

	//________________Sequence number
	sq = header[7]; //[1]
}

void DeFrame::UnPack(std::vector<std::bitset<8>> package) {

	oldsq = sq; //Opdater oldsq 

	try {
		Hi(package[0]); //Get header information
	}
	catch (const std::out_of_range & oor) {//Check for vector out of range
		std::cerr << "Out of Range error: " << oor.what() << '\n';
		return;
	}

	if (dataSize != (package.size() - 2)) //If some data was lost
	{
		std::cout << "Length of data recieved is not equal to length in header." << std::endl;
		return;
	}
	if(package.size() < 2)
	{
		std::cout << "Length of data too short, package discarded." << std::endl;
		return;
	}

	//Hi(package[0]); //Get header information
	header = package[0]; //save header
	trailer = package[dataSize+1]; //save trailer
	bool crcCheck;
	bool dubletCheck;

	std::bitset<8> workingByte;

	//Tøm datagram
	datagram = {};

	for (size_t i = 1; i <= dataSize; i++)
	{
		workingByte = package[i];
		datagram.push_back(workingByte);
	}

	//Add til package collector
	//SKAL ske til sidst i funktionen
	crcCheck = CrcCheck();
	dubletCheck = DoubletCheck();
	packageCollector.AddToCollector(crcCheck, dubletCheck, dataSize, sp, datagram);
}

std::vector<std::bitset<8>> DeFrame::getDatagram() {
	//LOOP FOR TEST
	//for (size_t i = 0; i < datagram.size(); i++)
	//{
	//	std::cout << datagram[i] << ", ";
	//}
	return datagram;
}

bool DeFrame::CrcCheck() {
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

	//TIL TEST!
	//for (size_t i = 0; i < vecIntToCrcCheck.size(); i++)
	//{
	//	std::cout << vecIntToCrcCheck[i] << ",";
	//}

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
 
//std::vector<std::bitset<8>> DeFrame::getPackageContainer() {
//	return packageCollector.packageContainer;
//}