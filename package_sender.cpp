#include "package_sender.h"

PackageSender::PackageSender(){}
PackageSender::~PackageSender(){}

void PackageSender::SendMessage(std::vector<std::bitset<8>> message) {
	framer.MessageCutter(message); //Del beskeden op og pak dem ind
	toSend = framer.GetPackages(); //Retunerer vektor med pakker
	std::chrono::seconds waitTime(10); //Tid at vendte på ACK i sekunder
	std::chrono::seconds wtNextPck(1); //Tid at vendte med at sende næste pakke  i sekunder


	for (size_t i = 0; i < toSend.size(); i++) //Send hver pakke
	{
		SoundGenerator soundGenerator;
		DeFrame deFrame;

		//Er der modtaget et ACK fra forrige pakke
		//Vent i wtNextPck tid med at sende næste pakke, for at give modtager en chance for at følje med.
		if (DeFrame::ack)
		{
			std::this_thread::sleep_for(wtNextPck);
		}

		DTMFRecorder::pauseRecording = true; // stop med at lytte
		soundGenerator.convertToDTMF(toSend[i]);  //Kalder funktion fra fysisk lag til at sende en pakke som argument
		DTMFRecorder::pauseRecording = false; // start med at lytte igen
		std::this_thread::sleep_for(waitTime); //Vent på at modtage ACK

		while (!DeFrame::ack) //Se om ACK er modtaget
		{
			DTMFRecorder::pauseRecording = true; // stop med at lytte
			soundGenerator.convertToDTMF(toSend[i]); //Send samme pakke igen
			DTMFRecorder::pauseRecording = false; // start med at lytte igen
			std::this_thread::sleep_for(waitTime); // vent på ACK
		}
		//TO DO: RESET ACK
		deFrame.ack = false;
	}
}