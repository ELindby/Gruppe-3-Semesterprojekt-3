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

void Frame::MessageCutter(char message[]) {

	int byteIndex = 0;
	int pckIndex = 0;
	int msgSize = strlen(message);
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

	while (byteIndex < msgSize) //Er betingelsen IKKE opfyldt -> Alle tegn i beskeden er delt i vektorer af størrelsen "dataSize"
	{
		datagram = {}; //tøm datagram vektor

		pckIndex++;
		dataLeft = msgSize - byteIndex;
		for (size_t i = 0; i < maxDataSize; i++)
		{
			if (i < dataLeft)
			{
				datagram.push_back(std::bitset<8>(message[byteIndex])); //int(message[i]) parse char til decimal-tal
				byteIndex++;
			}
		}

		if (antalPakker <= pckIndex)
		{
			lastPck = true;
		}

		datagramSize = datagram.size();

		datagram.insert(datagram.begin(), AddHeader(lastPck, datagramSize)); //Tilføj header til pakke
		slicedMessage.push_back(datagram); //Indsæt pakke i Array med paker der udgør en besked
	}
}

std::vector<std::vector<std::bitset<8>>> Frame::GetPackages() {
	return slicedMessage;
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
		std::cout << "Datagram size:" << frame.size() -1 << std::endl;
	}
	std::cout << "Der er " << slicedMessage.size() << " pakker" << std::endl;
}