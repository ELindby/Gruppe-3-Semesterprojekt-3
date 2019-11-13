// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <vector>

class someCrc {

public:

	void senderPreb(std::vector<int> messageInput)  // The vector should look like { 1, 0, 1, 0, 1, 0, 0, 0, 1 }
	{
		int messageLength = messageInput.size();

		//Copy array into another arrays for processing

		temp = messageInput;
		finalMessage = messageInput;

		std::cout << "\n Original message :"; // Prints the original message
		for (i = 0; i < messageLength; i++)
		{
			std::cout << temp[i];
		}

		//Padding some zeros on the end of the message
		for (int i = messageLength; i < genLength + (messageLength - 1); i++)
		{
			temp.push_back(0);
		}

		std::cout << "\n Message after appending 0's :";
		for (i = 0; i < messageLength + genLength - 1; i++)
		{
			std::cout << temp[i];
		}
		std::cout << "\n";

		for (int i = 0; i < messageLength; i++) //Bitwise division
		{ // Her ligger fejlen!
			if (generator[0] == temp[i])
			{
				for (int j = 0, k = i; j < genLength; j++, k++)
				{
					if ((temp[k] == 1 && generator[j] == 1) || (temp[k] == 0 && generator[j] == 0))
					{
						temp.at(k) = 0;
					}
					else
					{
						temp.at(k) = 1;
					}
				}
			}

		}




		std::cout << "\n Message after division: ";
		for (i = 0; i < messageLength + genLength - 1; i++)
		{
			std::cout << temp[i];
		}
		std::cout << "\n";

		std::cout << "\n CRC : ";
		for (int i = 0; i < genLength - 1; i++)
		{
			std::cout << temp[messageLength + i] << " ";
			CRC.push_back(temp[messageLength + i]);

		}

		std::cout << "\n CRC Value: ";
		for (i = 0; i < genLength - 1; i++)
		{
			std::cout << CRC[i];
		}
		std::cout << "\n";



		// Add CRC-check "sum" to the message to be transmitted.
		for (int i = 0; i < genLength - 1; i++)
		{
			finalMessage.push_back(CRC[i]);
		}

		//Final message:
		std::cout << " The final message is: ";
		for (i = 0; i < messageLength + genLength - 1; i++)
		{
			std::cout << finalMessage[i];
		};
		std::cout << "\n";
	}

	void receiverCheck(std::vector<int> messageInput)
	{

		int messageLength = messageInput.size();
		temp = messageInput;


		for (int i = 0; i < messageLength - 1; i++) //Bitwise division
		{ // Her ligger fejlen!
			k = i;
			j = 0;
			if (generator[j] == temp[k])
			{
				for (int j = 0, k = i; j < genLength && k < messageLength; j++, k++)
				{
					if ((temp[k] == 1 && generator[j] == 1) || (temp[k] == 0 && generator[j] == 0))
					{
						temp.at(k) = 0;
					}
					else
					{
						temp.at(k) = 1;
					}
				}
			}

		}
		std::cout << "\n Message after division: ";
		for (i = 0; i < messageLength; i++)
		{
			std::cout << temp[i];
		}


		std::cout << "\n Remainder: ";

		/*for (i = messageLength,  j = 0; i < messageLength + (genLength-1); i++, j++)
		{
			rrem.push_back(temp.at(i));
		}*/



		for (i = 0; i < (messageLength); i++)
		{
			std::cout << temp[i];
		}

		int flag = 0;
		for (i = 0; i < (messageLength); i++)
		{
			if (temp[i] != 0)
			{
				flag = 1; // Error detected
			}
		}

		if (flag == 0)
		{
			std::cout << "\n Correct";
		}
		else
		{
			std::cout << "\n Contains Error";
		}
	}

private:

	std::vector<int> generator = { 1, 1, 0, 1 }; //A better generator must be choosen!
	int genLength = generator.size();
	std::vector<int> temp, CRC, finalMessage, rrem;
	int i, k, j;
	bool flag;

};





int main()
{
	std::vector<int> test = { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0 , 0, 0, 1, 0, 0, 0, 0, 1 }; //Hej!
	std::vector<int> receiveTestCorrect = { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1 };
	std::vector<int> receiveTestError = { 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1 };
	someCrc CRC;
	CRC.senderPreb(test);

	std::cout << " \n Test correct:";
	CRC.receiverCheck(receiveTestCorrect);
	std::cout << " \n \n Test with error:";
	CRC.receiverCheck(receiveTestError);


	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu