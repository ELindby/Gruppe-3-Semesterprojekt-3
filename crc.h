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

	std::vector<int> senderPreb(std::vector<int> messageInput);
	bool receiverCheck(std::vector<int> messageInput);

private:
	std::vector<int> generator = { 1, 0, 1, 1, 1, 1, 1, 1 }; //CRC-8-AUTOSAR
	int genLength = generator.size();
	std::vector<int> temp, codeWord, finalMessage;
	int i, k, j;
	bool errorFlag;
};
