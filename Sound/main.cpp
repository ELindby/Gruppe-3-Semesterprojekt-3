#include "send.h"
#include "receive.h"

#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>
#include <iomanip>

int main() {
	//std::string input;
	//getline(std::cin, input);
	//std::istringstream sstr(input);
	//char n;
	//std::vector<char> chars;
	//while (sstr >> std::noskipws >> n) {
	//	chars.push_back(n);
	//}
	//// Play entered chars as DTMF tones
	//for (size_t i = 0; i < chars.size(); i++) {
	//	send message(chars[i]);
	//}
	//system("pause");
	
	receive record;



	return 0;
}

// Optimize speed - there is a pause between different characters, 
// might be desired, might not be. PlaySound is what makes it slow.
// Make classes
