#pragma once
#include <chrono>
#include <thread>

#include <iostream>

#include "frame.h"

class PackageSender
{
public:
	PackageSender();
	~PackageSender();
	void SendMessage(std::vector<std::bitset<8>> message);
private:
	std::vector<std::vector<std::bitset<8>>> toSend;
	int lol;
};