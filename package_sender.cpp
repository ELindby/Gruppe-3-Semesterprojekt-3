#include "package_sender.h"

PackageSender::PackageSender() {}
PackageSender::~PackageSender() {}

void PackageSender::SendMessage(std::vector<std::bitset<8>> message) {

	Frame framer;

	framer.MessageCutter(message); //Cut message into correct sizes, and incapsulate them into frames
	toSend = framer.GetPackages(); //Returns vector with packages
	std::chrono::seconds waitTime(5); //set time to wait for an acknowledge (in seconds)
	std::chrono::seconds wtNextPck(1); //set time to wait between sending packages (in seconds)

	for (size_t i = 0; i < toSend.size(); i++) //Send packages
	{
		SoundGenerator soundGenerator;

		if (i > 0) //on second package being sent or later, wait a small delay before sending next package, so recieving node can prepare after sending acknowledge
		{
			std::this_thread::sleep_for(wtNextPck);
		}
		DeFrame::ack = false;

		DTMFRecorder::pauseRecording = true;	// Stop listening
		soundGenerator.convertToDTMF(toSend[i]);// Call to physical layer to send package
		DTMFRecorder::pauseRecording = false;	// Start listening again
		std::this_thread::sleep_for(waitTime);	// Wait for acknowledge

		//Wait for acknowldge / resend if no acknowledge has been recieved
		while (!DeFrame::ack) //Check if ack has been recieved
		{
			DTMFRecorder::pauseRecording = true;	// Stop listening
			soundGenerator.convertToDTMF(toSend[i]);// Call to physical layer to send package
			DTMFRecorder::pauseRecording = false;	// Start listening again
			std::this_thread::sleep_for(waitTime);	// Wait for acknowledge
		}
	}
}