#include "deframe.h"


DeFrame::DeFrame() {};
DeFrame::~DeFrame() {};

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
	Hi(package[0]);

	std::bitset<8> workingByte;

	//Tøm datagram
	datagram = {};

	for (size_t i = 1; i <= dataSize; i++)
	{
		workingByte = package[i];
		datagram.push_back(workingByte);
	}
}

std::vector<std::bitset<8>> DeFrame::getDatagram() {
	//LOOP FOR TEST
	//for (size_t i = 0; i < datagram.size(); i++)
	//{
	//	std::cout << datagram[i] << ", ";
	//}
	return datagram;
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