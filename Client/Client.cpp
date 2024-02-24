#include "Client.h"
#include <fstream>
#include "Logger.h"

Client::Client() {
	logMessage("INFO", "Client", "Initializing client");
	logMessage("INFO", "FileHandler", "Searching for \'transfer.info\' file");
	ifstream file("transfer.info");
	if (!file.is_open())
		logMessage("INFO", "MyComponent", "This is a log message");
}