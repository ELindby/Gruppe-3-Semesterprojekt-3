#include "GUI.h"
#include <SFML/Audio.hpp>

GUI::GUI() : gui_thread(&GUI::setupGUI, this)
{
}

GUI::~GUI()
{
}

bool PackageCollector::static_spFlag;

void GUI::setupGUI()
{
	//Setup window
	sf::RenderWindow window(sf::VideoMode(800, 600), "DTMF-chat");

	sf::Image icon;
	icon.loadFromFile("phoneIcon.png");
	window.setIcon(350,350,icon.getPixelsPtr());

	//Load text font
	if (!font.loadFromFile("sansation.ttf"))
	{
		// Should throw error
		std::cout << "FONT FaiL!" << '\n';
	}

	while (window.isOpen())
	{
		
		eventCheck(window);

		addMessage();

		sf::Mutex mutex;
		mutex.lock();

		window.clear(sf::Color::White);

		drawTyping(window);
		drawConversation(window);

		window.display();

		mutex.unlock();

	} // End of while(window.isOpen())
}


void GUI::addMessage()
{
	if (!PackageCollector::static_spFlag) //Checks if PackageCollector has a complete message ready
	{
		return; 
	}
	std::vector<std::bitset<8>> recievedMessage = PackageCollector::GetMsg();

	std::string recievedMessageAsString = "";
	for (size_t i = 0; i < recievedMessage.size(); i++)
	{
		recievedMessageAsString += recievedMessage[i].to_ulong();
	}

	// Adds recieved message to printed conversation
	conversation.emplace_back(recievedMessageAsString, false); // true: I sent the message & false: I recieved the message
	PackageCollector::static_spFlag = false;
	PackageCollector::clearContainer();
}

void GUI::eventCheck(sf::RenderWindow& window)
{
	// Handle envent
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Window closed
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == 8 && (typedText.size() != 0)) // Test for "Backspace" key
			{
				typedText.pop_back();
			}

			// Send message by pressing enter
			else if (event.text.unicode == 13 && typedText.size() != 0) //Test for "Enter" key
			{
				// Send message as vector of bitset<8> to Data Link Layer 
				std::string nextMessage = typedText;
				conversation.emplace_back(nextMessage, true); // true: I sent the message & false: I recieved the message

				// Send typedText to Data link layer
				nextMessageAsBitset = {};
				for (size_t i = 0; i < nextMessage.size(); i++)
				{
					std::bitset<8> newBitset(nextMessage[i]);
					nextMessageAsBitset.push_back(newBitset);
				}

				packageSender.SendMessageA(nextMessageAsBitset);

				// Clear typedText temp
				typedText = "";
			}

			else
			{
				typedText.push_back(static_cast<char>(event.text.unicode)); //Add typed character to typedText
			}
		}
	} // End of event poll check
}

void GUI::drawConversation(sf::RenderWindow& window)
{
	float offset = typeingBoxHeight*nLines + edgeWidth + textDisplacement*2; //Offset from bottom of screen, decides where messages will be printed
	for (int i = conversation.size() - 1; i > -1; i--)
	{
		//Setup linesplit
		std::string tempMessageText = conversation[i].first;

		float sizeRatio = (float)tempMessageText.size() / (float)32;
		int mLines = ceil(sizeRatio);

		int remainderUpTo32b = 32;
		if (tempMessageText.size() < 32)
			remainderUpTo32b = tempMessageText.size();

		std::string tempLineText = tempMessageText.substr(0, remainderUpTo32b);
		
		//Create temporary first line, only used to set the size of the text bubble
		sf::Text textMessage; 
		textMessage.setFont(font);
		textMessage.setCharacterSize(24);
		textMessage.setString(tempLineText);

		//Make Textbox
		sf::FloatRect textBounds = textMessage.getLocalBounds();
		textBounds.height += 2.0;
		sf::RectangleShape textMessageBox(sf::Vector2f(textBounds.width + (boxEdgeWidth * 2), textBounds.height*mLines + (boxEdgeWidth*2)));

		float wordWrapOffset = ((float) mLines - 1.) * textBounds.height;
		if (conversation[i].second)
		{
			// If I sent the message
			textMessageBox.setFillColor(sf::Color::Blue);
			textMessageBox.move(window.getSize().x - textBounds.width - edgeWidth, window.getSize().y - offset - wordWrapOffset);
		}
		else
		{
			// If I recieved the message
			textMessageBox.setFillColor(sf::Color::Green);
			textMessageBox.move(edgeWidth, window.getSize().y - offset - wordWrapOffset);
		}
		window.draw(textMessageBox);

		for (size_t j = 0; j < mLines; j++)
		{
			// Setup single line to be printed
			sf::Text drawableTempMessageText;
			drawableTempMessageText.setFont(font);
			drawableTempMessageText.setCharacterSize(24);

			int remainderUpto32 = 32;
			if (tempMessageText.size() < 32)
				remainderUpto32 = tempMessageText.size();

			std::string tempLineText = tempMessageText.substr(0, remainderUpto32);
			tempMessageText.erase(0, remainderUpto32);

			drawableTempMessageText.setString(tempLineText);

			//Move messages to the right position in the frame
			if (conversation[i].second)
			{
				// If I sent the message
				drawableTempMessageText.setFillColor(sf::Color::White);
				drawableTempMessageText.move(window.getSize().x - textBounds.width + boxEdgeWidth - edgeWidth, window.getSize().y - offset - wordWrapOffset + j * textBounds.height);
			}
			else
			{
				// If I recieved the message
				drawableTempMessageText.setFillColor(sf::Color::Black);
				drawableTempMessageText.move(edgeWidth + boxEdgeWidth, window.getSize().y - offset - wordWrapOffset + j * textBounds.height);
			}
			window.draw(drawableTempMessageText);
		}
		offset += textMessageBox.getLocalBounds().height + textDisplacement; //Update offset after printing a message
	}
}

void GUI::drawTyping(sf::RenderWindow& window) //Draws the Typing box at the bottom of the screen
{
	// Make typing box
	sf::RectangleShape typeBox;
	typeBox.setFillColor(sf::Color::Color(180, 180, 180, 80/*216, 216, 216, 85*/));

	//drawableTypedText.getLocalBounds().width < window.getSize().x - edgeWidth * 2
	if (typedText.size() < 32)
	{
		nLines = 1;
		// Setup: TypedText
		sf::Text drawableTypedText;
		drawableTypedText.setFont(font);
		drawableTypedText.setCharacterSize(24);
		drawableTypedText.setFillColor(sf::Color::Black);
		drawableTypedText.setString(typedText);
		typeBox.setSize(sf::Vector2f(window.getSize().x - (2 * edgeWidth), typeingBoxHeight));
		typeBox.move(edgeWidth, window.getSize().y - edgeWidth);

		drawableTypedText.move(edgeWidth + boxEdgeWidth, window.getSize().y - edgeWidth);

		// Draw typing and typing box
		window.draw(typeBox);
		window.draw(drawableTypedText);
	}
	else
	{
		float sizeRatio = (float)typedText.size() / (float)32;
		nLines = ceil(sizeRatio);

		// Draw typing box
		typeBox.setSize(sf::Vector2f(window.getSize().x - (2 * edgeWidth), typeingBoxHeight * nLines));
		typeBox.move(edgeWidth, window.getSize().y - edgeWidth - typeingBoxHeight * (nLines - 1));
		window.draw(typeBox);

		std::string tempTypedText = typedText;
		for (size_t i = 0; i < nLines; i++)
		{
			// Setup: TypedText
			sf::Text drawableTempTypedText;
			drawableTempTypedText.setFont(font);
			drawableTempTypedText.setCharacterSize(24);
			drawableTempTypedText.setFillColor(sf::Color::Black);
			int remainderUpto32 = 32;
			if (tempTypedText.size() < 32)
				remainderUpto32 = tempTypedText.size();

			std::string tempLineText = tempTypedText.substr(0, remainderUpto32);
			tempTypedText.erase(0,remainderUpto32);

			drawableTempTypedText.setString(tempLineText);
			drawableTempTypedText.move(edgeWidth + boxEdgeWidth, window.getSize().y - edgeWidth - (nLines-1) * typeingBoxHeight + i * typeingBoxHeight);
			window.draw(drawableTempTypedText);
		}
	}
}