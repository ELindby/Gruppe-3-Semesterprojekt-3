#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <bitset>

class DeFrame
{
public:	
	DeFrame();
	~DeFrame();

	void UnPack(std::vector<std::bitset<8>> package);
	std::vector<std::bitset<8>> getDatagram();
	bool getAckFlag();
	bool getSpFlag();
	bool DoubletCheck();

private:

	//______Til Information om header________
	void Hi(std::bitset<8> package); //Header information i argument pakke

	bool sq; ////seq. nr. bit
	int dataSize; //Antal bytes i pakken
	bool sp; //Er det sidste pakke i beskeden
	bool ack; //Tjek om pakke er ack

	//______Datagram
	std::vector<std::bitset<8>> datagram;
	
	//______Til Dublet check________
	bool oldsq = 0;
};