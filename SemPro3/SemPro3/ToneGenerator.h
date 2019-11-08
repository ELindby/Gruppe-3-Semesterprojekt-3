#pragma once
#include "FysiskLag.h"
#include <SFML/Audio.hpp>
#include <iostream>

#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H

class ToneGenerator : public FysiskLag
{
public:
	ToneGenerator();
	~ToneGenerator();

	void PlaySound();
};
#endif // !TONEGENERATOR_H