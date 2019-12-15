#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <bitset> 

class CRC
{
public:
	CRC();
	~CRC();

	std::vector<int> senderPrep(std::vector<int> messageInput);
	bool receiverCheck(std::vector<int> messageInput);

private:
	std::vector<int> generator = { 1, 1, 0, 0, 1, 0, 1, 1, }; //CRC-7F/2
	int genLength = generator.size();
	std::vector<int> temp, codeWord, finalMessage;
	int i, k, j;
	bool errorFlag;
};
