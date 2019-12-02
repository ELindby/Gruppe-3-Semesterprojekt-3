#include "frame.h"

Frame::Frame() {};
Frame::~Frame() {};

std::bitset<8> Frame::AddHeader(bool lastPackage, int size) {
	std::string header;

	dataSize = std::bitset<5>(size);
	sq = ~sq; //seq. nr. bit
	sp = std::bitset<1>(lastPackage);

	header = sq.to_string() + sp.to_string() + "0" + dataSize.to_string();
	return std::bitset<8>(header);
}

//void Frame::MessageCutter(char message[]) {
//
//	int byteIndex = 0;
//	int pckIndex = 0;
//	int msgSize = strlen(message);
//	int antalPakker = ceil(msgSize / maxDataSize) + 1;
//	bool lastPck = false;
//	std::vector<std::bitset<8>> datagram;
//	int datagramSize = 0;
//	int dataLeft;
//
//	if (msgSize <= 0) //Hvis besked er tom. Tilføj kun header
//	{
//		lastPck = true;
//		datagram = { AddHeader(lastPck, datagramSize) };
//		slicedMessage.push_back(datagram);
//	}
//
//	while (byteIndex < msgSize) //Er betingelsen IKKE opfyldt
//	{
//		datagram = {}; //tøm datagram vektor
//
//		pckIndex++;
//		dataLeft = msgSize - byteIndex;
//		for (size_t i = 0; i < maxDataSize; i++)
//		{
//			if (i < dataLeft)
//			{
//				datagram.push_back(std::bitset<8>(message[byteIndex])); //int(message[i]) parse char til decimal-tal
//				byteIndex++;
//			}
//		}
//
//		if (antalPakker <= pckIndex)
//		{
//			lastPck = true;
//		}
//
//		datagramSize = datagram.size();
//
//		datagram.insert(datagram.begin(), AddHeader(lastPck, datagramSize)); //Tilføj header til pakke
//
//		//!Det er er vigtigt at header kommer på før datagrammet! 
//		AddTrailer(datagram);
//		datagram.push_back(crcCodeword); //Tilføj trailer til pakke (SKAL HAVE HEADER MED)
//
//		slicedMessage.push_back(datagram); //Indsæt pakke i Array med paker der udgør en besked
//	}
//}

void Frame::MessageCutter(std::vector<std::bitset<8>> message) {

	int byteIndex = 0;
	int pckIndex = 0;
	int msgSize = message.size();
	int antalPakker = ceil(msgSize / maxDataSize) + 1;
	bool lastPck = false;
	std::vector<std::bitset<8>> datagram;
	int datagramSize = 0;
	int dataLeft;

	if (msgSize <= 0) //Hvis besked er tom. Tilføj kun header
	{
		lastPck = true;
		datagram = { AddHeader(lastPck, datagramSize) };
		slicedMessage.push_back(datagram);
	}

	while (byteIndex < msgSize) //Er betingelsen IKKE opfyldt
	{
		datagram = {}; //tøm datagram vektor

		pckIndex++;
		dataLeft = msgSize - byteIndex;
		for (size_t i = 0; i < maxDataSize; i++)
		{
			if (i < dataLeft)
			{
				datagram.push_back(message[byteIndex]); //int(message[i]) parse char til decimal-tal
				byteIndex++;
			}
		}

		if (antalPakker <= pckIndex)
		{
			lastPck = true;
		}

		datagramSize = datagram.size();

		datagram.insert(datagram.begin(), AddHeader(lastPck, datagramSize)); //Tilføj header til pakke

																			 //!Det er er vigtigt at header kommer på før datagrammet! 
		AddTrailer(datagram);
		datagram.push_back(crcCodeword); //Tilføj trailer til pakke (SKAL HAVE HEADER MED)

		slicedMessage.push_back(datagram); //Indsæt pakke i Array med paker der udgør en besked
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
	//std::vector<int> testdata = {1,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0};

	std::vector<int> fromCRC = {};
	std::string str_codeWord = "";

	for (size_t i = 0; i < hd.size(); i++)
	{
		for (size_t j = 0; j < 8; j++) //!!!!
		{
			toCRC.push_back(hd[i][7 - j]);
		}
	}

	//_________________TIL TEST_______toCRC vektor<int> 
	//for (size_t i = 0; i < toCRC.size(); i++)
	//{
	//	std::cout << toCRC[i] << ",";
	//}
	//std::cout << std::endl;
	//_____________

	fromCRC = crcClass.senderPreb(toCRC); //Få Codeword

	//std::cout << " " << fromCRC.size() << std::endl;

	for (size_t i = 0; i < fromCRC.size(); i++)
	{
		//std::cout << fromCRC[i] << " ";
		str_codeWord += std::to_string(fromCRC[i]);
	}

	crcCodeword = std::bitset<8>(str_codeWord);
}

//TIL TESTING
void Frame::PrintMsgSliced() {
	for (size_t i = 0; i < slicedMessage.size(); i++)
	{
		std::vector<std::bitset<8>> frame = slicedMessage[i];
		int l = frame.size();

		std::cout << "{";
		for (size_t t = 0; t < l; t++)
		{
			std::cout << frame[t] << ", ";
		}
		std::cout << "}" << std::endl;
		std::cout << "Datagram size:" << frame.size() -2 << std::endl;
	}
	std::cout << "Der er " << slicedMessage.size() << " pakker" << std::endl;
}