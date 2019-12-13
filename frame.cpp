#include "frame.h"

Frame::Frame() {};
Frame::~Frame() {};

std::bitset<1> Frame::sq = 0;

std::bitset<8> Frame::AddHeader(bool lastPackage, int size) { //Add header to package
	std::string header;

	dataSize = std::bitset<5>(size);
	sp = std::bitset<1>(lastPackage); //last package flag
	sq = ~sq; //seq. nr. bit
	header = sq.to_string() + sp.to_string() + "0" + dataSize.to_string();
	return std::bitset<8>(header);
}

void Frame::MessageCutter(std::vector<std::bitset<8>> message) 
{
	int byteIndex = 0;
	int pckIndex = 0;
	int msgSize = message.size();
	float sizeRatio = (float)msgSize / (float)maxDataSize;
	int antalPakker = ceil(sizeRatio);
	bool lastPck = false;
	std::vector<std::bitset<8>> datagram = {};
	int datagramSize = 0;
	int dataLeft;

	if (msgSize <= 0) //If message is empty, only add header and trailer (If message is empty, it's an acknowledge package)
	{
		lastPck = true;

		datagram = { (AddHeader(lastPck, datagramSize)) }; //Add header to package

		AddTrailer(datagram);
		datagram.push_back(trailer); //Add trailer to package

		slicedMessage.push_back(datagram); //Adds completed frame to list of frames
		return;
	}

	while (byteIndex < msgSize) //Runs through the entire message.
	{
		datagram = {}; //Clear datagram (payload)

		pckIndex++;
		dataLeft = msgSize - byteIndex;
		for (size_t i = 0; i < maxDataSize; i++)
		{
			if (i < dataLeft)
			{
				datagram.push_back(message[byteIndex]); //int(message[i]) parse char to decimal
				byteIndex++;
			}
		}

		if (antalPakker <= pckIndex)
		{
			lastPck = true;
		}

		datagramSize = datagram.size();
		datagram.insert(datagram.begin(), AddHeader(lastPck, datagramSize)); //Add header to package

		AddTrailer(datagram);
		datagram.push_back(trailer); //Add trailer to package

		slicedMessage.push_back(datagram); //Adds completed frame to list of frames
	}
}

std::vector<std::vector<std::bitset<8>>> Frame::GetPackages() {
	return slicedMessage;
}

void Frame::AddTrailer(std::vector<std::bitset<8>> headerAndDatagram) {
	CRC crcClass;

	std::vector<std::bitset<8>> hd = headerAndDatagram;
	std::vector<int> tempByte;
	std::vector<int> toCRC = {};
	
	std::vector<int> fromCRC = {};
	std::string str_codeWord = "";

	for (size_t i = 0; i < hd.size(); i++)
	{
		for (size_t j = 0; j < 8; j++) //!!!!
		{
			toCRC.push_back(hd[i][7 - j]);
		}
	}

	fromCRC = crcClass.senderPrep(toCRC); //Get Codeword

	for (size_t i = 0; i < fromCRC.size(); i++)
	{
		str_codeWord += std::to_string(fromCRC[i]);
	}
	trailer = std::bitset<8>(str_codeWord).set(7); //.set(7) sets bit at 7 to 1: [1]xxxxxxx
}
