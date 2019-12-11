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

	
	void setupGUI();
	void addMessage();
	void eventCheck(sf::RenderWindow &window);
	void drawConversation(sf::RenderWindow& window);
	void drawTyping(sf::RenderWindow& window);

	
	// Skal nedenstående være public?????
	typedef std::pair<std::string, bool> conversationType;
	//static conversationType staticConversationType;
	std::vector<std::pair<std::string, bool>> conversation;

	
private:
	sf::Font font;
	
	sf::Thread gui_thread;

	PackageSender packageSender;

	// storing conversation as string in vector
	std::string typedText = "";
	
	
	std::vector<std::bitset<8>> nextMessageAsBitset;

	// interface setup
	float edgeWidth = 40.0;
	float typeingBoxHeight = 30.0;
	float boxEdgeWidth = 10.0;
	float textDisplacement = 10.0;
	int nLines = 1;
	float messageBoxLineHeight = 30.0;

	//// special danish characters
	//std::vector<int> specialCharacters = {230, 198, 248, 216, 229, 197};


};