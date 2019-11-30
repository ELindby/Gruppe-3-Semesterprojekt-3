#pragma once
#include <chrono>
#include <thread>

#include <iostream>

#include "frame.h"
#include "deframe.h"

Frame framer;
bool DeFrame::ack;

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