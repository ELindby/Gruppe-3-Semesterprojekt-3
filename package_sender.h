#pragma once
#include <chrono>
#include <thread>
#include <iostream>

#include "frame.h"
#include "SoundGenerator.h"
#include "Recorder.h"
#include "deframe.h"

class PackageSender
{
public:
	PackageSender();
	~PackageSender();
	void SendMessage(std::vector<std::bitset<8>> message);
	Frame framer;
private:
	std::vector<std::vector<std::bitset<8>>> toSend;
};