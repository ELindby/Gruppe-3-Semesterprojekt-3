#pragma once
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>

class Send
{
public:
	Send();
	~Send();
	Send(char n);

	void ConvertToDTMF(char input);
	int lowtoneFrequency(char low);
	int hightoneFrequency(char high);
	void PlaySound(int lowDTMFL, int highDTMFL, int lowDTMFU, int highDTMFU);
};

