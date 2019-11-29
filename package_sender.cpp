#include "package_sender.h"

PackageSender::PackageSender(){}
PackageSender::~PackageSender(){}

Frame framer;

void PackageSender::SendMessage(std::vector<std::bitset<8>> message) {
	framer.MessageCutter(message); //Del beskeden op og pak dem ind
	toSend = framer.GetPackages(); //Retunerer vektor med pakker
	std::chrono::seconds waitTime(1); //Tid at vendte på ACK i sekunder
	bool gotAck = false;

	for (size_t i = 0; i < toSend.size(); i++) //Send hver pakke
	{
		SendPackage(toSend[i]); //Kalder funktion fra fysisk lag til at sende en pakke som argument

		std::this_thread::sleep_for(waitTime);//Vent på at modtage ACK
		gotAck = getAck(); //Retunerer true hvis sidste deframed pakke er et ack (datgram længde = 0)
		while (!gotAck)
		{
			//Se om ACK er modtaget
			SendPackage(toSend[i]);//Send samme pakke igen
			std::this_thread::sleep_for(waitTime);
			gotAck = getAck(); //Retunerer true hvis sidste deframed pakke er et ack (datgram længde = 0)
		}
	}
}