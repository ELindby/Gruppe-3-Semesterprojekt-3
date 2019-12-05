#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "package_sender.h"
#include "package_collector.h"

#include <iostream>
#include <bitset>
#include <algorithm>

class GUI
{
public:
	GUI();
	~GUI();

	//static GUI& GUIinstance();

	void setupGUI();
	void addMessage(std::vector<std::bitset<8>> recievedMessage);

	typedef std::pair<std::string, bool> conversationType;
	//static conversationType staticConversationType;
	std::vector<std::pair<std::string, bool>> conversation;

	//// Test:
	//static void test(std::vector<std::bitset<8>> recievedMessage);

	////static std::vector<conversationType> bob;
	//
	//static std::vector<std::string> conversationString;
	//static std::vector<bool> conversationBool;

private:
	sf::Font font;
	sf::Text drawableTypedText;
	sf::Thread gui_thread;

	PackageSender packageSender;

	// storing conversation as string in vector
	std::string typedText = "";
	
	
	std::vector<std::bitset<8>> nextMessageAsBitset;

	// interface setup
	float edgeWidth = 40.0;
	float typeingBoxHeight = 30.0;
	float boxEdgeWidth = 10.0;
	float textDisplacement = 30.0;

	//// special danish characters
	//std::vector<int> specialCharacters = {230, 198, 248, 216, 229, 197};


};