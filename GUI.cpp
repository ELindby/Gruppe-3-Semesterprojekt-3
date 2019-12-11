#include "GUI.h"
#include <SFML/Audio.hpp>

GUI::GUI() : gui_thread(&GUI::setupGUI, this)
{
	//std::cout << "I'm the gui thread" << '\n';
}

GUI::~GUI()
{
}

bool PackageCollector::static_spFlag;
//std::vector<std::bitset<8>> PackageCollector::GetMsg();
//std::vector<std::bitset<8>> PackageCollector::packageContainer;

void GUI::setupGUI()
{
	//std::cout << "I'm the setupGUI function" << '\n';

	//Setup window
	sf::RenderWindow window(sf::VideoMode(800, 600), "DTMF-chat");
	//window.setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("hammer.png");
	window.setIcon(350,350,icon.getPixelsPtr());

	//Load text font
	if (!font.loadFromFile("sansation.ttf"))
	{
		// Should trow error
		std::cout << "FONT FaiL!" << '\n';
	}

	// Make typing box
	sf::RectangleShape typeBox(sf::Vector2f(window.getSize().x - (2 * edgeWidth), typeingBoxHeight));
	typeBox.setFillColor(sf::Color::Color(180, 180, 180, 80/*216, 216, 216, 85*/));
	typeBox.move(edgeWidth, window.getSize().y - edgeWidth);


	// Setup: TypedText
	drawableTypedText.setFont(font);
	drawableTypedText.setCharacterSize(24);
	drawableTypedText.setFillColor(sf::Color::Black);
	drawableTypedText.move(edgeWidth + boxEdgeWidth, window.getSize().y - edgeWidth);


	while (window.isOpen())
	{
		// Handle envent
		sf::Event event;
		while (window.pollEvent(event))
		{
			//std::cout << "poll event tjek" << '\n';

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
					//// add typedText to 
					//pendingMessages.push_back(typedText);

					// Send message as vector of bitset<8> to Data Link Layer 
					std::string nextMessage = typedText;
					conversation.emplace_back(nextMessage, true); // true: I sent the message & false: I recieved the message

					nextMessageAsBitset = {};
					for (size_t i = 0; i < nextMessage.size(); i++)
					{
						std::bitset<8> newBitset(nextMessage[i]);
						nextMessageAsBitset.push_back(newBitset);
					}

					packageSender.SendMessageA(nextMessageAsBitset);

					// empty typedText temp
					typedText = "";
				}

				else /*if (event.text.unicode < 128 || std::find(specialCharacters.begin(), specialCharacters.end(), event.text.unicode) != specialCharacters.end() )*/
				{
					//std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) <<  std::endl;	
					//std::cout << "unicode for typed character: " << event.text.unicode << std::endl;

					//typedText.push_back((char)event.text.unicode);

					typedText.push_back(static_cast<char>(event.text.unicode));
				}

				//std::cout << "TypedText: " << typedText << std::endl;
			}

		} // End of event poll check

		sf::Mutex mutex;
		mutex.lock();

		window.clear(sf::Color::White);

		float iterator = typeingBoxHeight + edgeWidth + textDisplacement;
		//std::reverse(conversation.begin(), conversation.end());
		for (int i = conversation.size() - 1; i > -1; i--)
		{
			// Setup textMessage and box:

			// Setup textMessage
			sf::Text textMessage;
			textMessage.setFont(font);
			textMessage.setCharacterSize(24);

			textMessage.setString(conversation[i].first);

			// Make Textbox
			sf::FloatRect textBounds = textMessage.getLocalBounds();
			sf::RectangleShape textMessageBox(sf::Vector2f(textBounds.width + (boxEdgeWidth * 2), textBounds.height + (boxEdgeWidth * 2)));


			// move messages & messageBoxes to the right position in the frame
			if (conversation[i].second)
			{
				// If I sent the message
				textMessage.setFillColor(sf::Color::White);
				textMessageBox.setFillColor(sf::Color::Blue);

				textMessage.move(edgeWidth + window.getSize().x / 2 + boxEdgeWidth, window.getSize().y - iterator);
				textMessageBox.move(edgeWidth + window.getSize().x / 2, window.getSize().y - iterator);
			}
			else
			{
				// If I recieved the message
				textMessage.setFillColor(sf::Color::Black);
				textMessageBox.setFillColor(sf::Color::Green);

				textMessage.move(edgeWidth + boxEdgeWidth, window.getSize().y - iterator);
				textMessageBox.move(edgeWidth, window.getSize().y - iterator);
			}

			iterator += textBounds.height + textDisplacement; // iterator til teksforskydning

			window.draw(textMessageBox);
			window.draw(textMessage);
		}

		// Draw typing and typing box
		window.draw(typeBox);
		drawableTypedText.setString(typedText);
		window.draw(drawableTypedText);

		addMessage();
		//addMessage(PackageCollector::GetMsg()); //Tilføjer modtaget besked til display listen
		// PackageCollector::clearContainer(); //Clear container

		//std::cout << '\n' << "window display" << '\n';
		window.display();

		mutex.unlock();

	} // End of while(window.isOpen())

}

//void GUI::addMessage(std::vector<std::bitset<8>> recievedMessage)
void GUI::addMessage()
{
	
	if (!PackageCollector::static_spFlag) //Gå ud af scope hvis det ikke er den sidste pakke i beskeden.
	{
		return; 
	}
	//std::cout << "PackCol spFlag: " << PackageCollector::static_spFlag;
	std::vector<std::bitset<8>> recievedMessage = PackageCollector::GetMsg();

	std::string recievedMessageAsString = "";
	for (size_t i = 0; i < recievedMessage.size(); i++)
	{
		recievedMessageAsString += recievedMessage[i].to_ulong();
	}

	//std::cout << "adMessage function" << '\n';

	// Adds recieved message to printed conversation
	conversation.emplace_back(recievedMessageAsString, false); // true: I sent the message & false: I recieved the message
	PackageCollector::static_spFlag = false;
	PackageCollector::clearContainer();
}
