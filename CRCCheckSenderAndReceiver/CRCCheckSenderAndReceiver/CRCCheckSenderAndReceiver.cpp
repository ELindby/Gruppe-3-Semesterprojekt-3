// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <bitset> 

class CRC {

public:

	std::vector<int> senderPreb(std::vector<int> messageInput)  // The vector should look like { 1, 0, 1, 0, 1, 0, 0, 0, 1 }
	{
		int messageLength = messageInput.size();

		//Copy array into another arrays for processing

		temp = messageInput;
		finalMessage = messageInput;

		
		//Padding some zeros on the end of the message
		for (int i = messageLength; i < genLength + (messageLength - 1); i++)
		{
			temp.push_back(0);
		}


		for (int i = 0; i < messageLength; i++) //Bitwise division
		{ 
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

	
		for (int i = 0; i < genLength - 1; i++)
		{			
			CRC.push_back(temp[messageLength + i]);
		}

		
		// Add CRC-check "sum" to the message to be transmitted.
		for (int i = 0; i < genLength - 1; i++)
		{
			finalMessage.push_back(CRC[i]);
		}

		// Returns the final message as a vector containing int
		return finalMessage;
	}


	bool receiverCheck(std::vector<int> messageInput)
	{

		int messageLength = messageInput.size();
		temp = messageInput;


		for (int i = 0; i < messageLength - 1; i++) //Bitwise division
		{ 
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
		
		int errorFlag = 0; // Flag that is set if an error is detected
		for (i = 0; i < (messageLength); i++) // Checks if error has been detekted, sets errorflag if true.
		{
			if (temp[i] != 0)
			{
				errorFlag = 1; // Error detected
			}
		}

		if (errorFlag == 0) // Returns bool value, 1 for no error and 0 for error. 
		{
			return 1;	
		}
		else
		{
			return 0; 
		}
	}

private:

	std::vector<int> generator = { 1, 1, 0, 1, 0, 1, 1, 1 }; //CRC-8-AUTOSAR
	int genLength = generator.size(); 
	std::vector<int> temp, CRC, finalMessage;
	int i, k, j;
	bool errorFlag;

};





int main()
{
	std::vector<int> test =               { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; //Hej!
	CRC CRC;
	if (CRC.receiverCheck(CRC.senderPreb(test)) == 1)
	{
		std::cout << "\n Correct";
	}
	else
	{
		std::cout << "Error";
	};
	
		

	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu