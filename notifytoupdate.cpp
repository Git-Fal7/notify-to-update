/*
* Update to notify
* Made by KamaKazeh
*
* Update to notify is a program that sends notification via libnotify (notify-send).
*/

#include <stdio.h>
#include <string>
#include <unistd.h>
using namespace std;

//Using popen to output
string popenStdout(string cmd) {
	string data;
	FILE* stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");

	if (stream) {
		while (!feof(stream)) {
			if (fgets(buffer, max_buffer, stream) != NULL)
				data.append(buffer);
		}
		pclose (stream);
	}
	return data;
}

int main() {
	unsigned int microminutes = 60000000;
	while (true) {
		string out = popenStdout("apt-get -o DEbug::NoLocking=true --trivial-only -V dist-upgrade");
		//If output doesn't contain this, send notification
		if (out.find("0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.") == string::npos)
			system("notify-send -i /usr/share/icons/Papirus-Dark/32x32/emblems/emblem-downloads.svg 'Updates Avaliable' 'Please open synaptic and update'");
		//Minutes * 60 seconds in microseconds
		usleep(150 * microminutes);
	}
}
