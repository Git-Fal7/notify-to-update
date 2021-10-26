/*
* Update to notify
* Made by KamaKazeh
*
* Update to notify is a program that sends notification via libnotify (notify-send).
*/

#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;

string otToString(string cmd) {
	char *command = (char *) (cmd + " > /tmp/fileUTO22.txt").c_str();
	system(command);
	string data;

	ifstream file("/tmp/fileUTO22.txt"); 

	if (file.is_open()) {
		file >> data;
	}

	return data;
}


int main() {
	unsigned int microminute = 60000000;
	while (true) {
		string out = otToString("apt-get -q -y --ignore-hold --allow-change-held-packages --allow-unauthenticated -s dist-upgrade | /bin/grep  ^Inst | wc -l");
		if (out != "0"){
			string uptxt;
			if (out == "1")
				uptxt = "an update is";
			else 
				uptxt = (oof + "updates are");
			system(("notify-send -i /usr/share/icons/Papirus-Dark/32x32/emblems/emblem-downloads.svg 'Updates Avaliable' 'Open Synaptic, " + uptxt + " avaliable'").c_str());
		}
		//Minutes * 60 seconds in microseconds
		usleep(150 * microminute);
	}
}
