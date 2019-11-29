#pragma once
#include <iostream>

#include "deframe.h"

class PackageCollector
{
public:
	PackageCollector();
	~PackageCollector();

	void AddToCollector();
	void SendACK();
	void MessageToApp();

private:
	std::vector<std::bitset<8>> packageContainer;
};
