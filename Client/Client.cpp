#include "Client.h"

Client::Client() {
	logMessage("INFO", "Client", "Initializing client");
	logMessage("INFO", "FileHandler", "Searching for \'transfer.info\' file");
	this->_err = 0;
	ifstream file("transfer.info");
	if (!file.is_open()) {
		logMessage("ERROR", "FileHandler", "Can not open or read \'transfer.info\' file");
		logMessage("ERROR", "FileHandler", "Make sure that the file exist with an access to it");
		this->_err = -1;
	}
	else {
		logMessage("INFO", "FileHandler", "File \'transfer.info\' was found successfuly");
		logMessage("INFO", "FileHandler", "Scanning \'transfer.info\' file");
		string first_line;
		string second_line;
		string third_line;
		int count_errors = 0;
		if (!getline(file, first_line)) count_errors++;
		if (!getline(file, second_line)) count_errors++;
		if (!getline(file, third_line)) count_errors++;
		if (count_errors > 0) {
			logMessage("ERROR", "Client", "File \'transfer.info\' integrity is not valid");
			logMessage("ERROR", "Client", "Make sure the file has 3 lines:");
			logMessage("ERROR", "Client", "<ADDRESS>:<PORT>");
			logMessage("ERROR", "Client", "<USER>");
			logMessage("ERROR", "Client", "<FILE_PATH>");
			logMessage("ERROR", "Client", "---------- Example ----------");
			logMessage("ERROR", "Client", "127.0.0.1:1234");
			logMessage("ERROR", "Client", "Micheal Jackson");
			logMessage("ERROR", "Client", "New_product_spec.docx");
			this->_err = -1;
		}
		else {
			// Validate inputs
			size_t pos = first_line.find(':');
			if (pos != string::npos) {
				this->_port = first_line.substr(pos + 1);
				this->_address = first_line.substr(0, pos);
				this->_user = second_line;
				this->_path = third_line;
				logMessage("INFO", "FileHandler", "File \'transfer.info\' has been read successfuly");
			}
			else {
				logMessage("ERROR", "StringHandler", "In the first line could not find \':\'");
				logMessage("ERROR", "Client", "Make sure the first line has <ADDRESS>:<PORT>");
				logMessage("ERROR", "Client", "---------- Example ----------");
				logMessage("ERROR", "Client", "127.0.0.1:1234");
				count_errors++;
			}
			if (count_errors > 0) this->_err = -1;
			else {
				try
				{
					int p = stoi(this->_port);
					if (p >= 0 && p <= 65353) {
						this->_port = to_string(p);
						logMessage("INFO", "Client", "Your port is a valid positive integer: " + this->_port);
					}

					else {
						logMessage("ERROR", "Client", "Your port is not a valid number.");
						logMessage("ERROR", "Client", "Make sure the port is a number between 0 to 65353.");
						logMessage("ERROR", "Client", "Your port is: " + this->_port);
						count_errors++;
					}
				}
				catch (const std::exception&)
				{
					logMessage("ERROR", "StringToIntegerHandler", "An error occured during the conversion of the port to an Integer.");
					logMessage("ERROR", "Client", "Make sure the port is a number between 0 to 65353.");
					logMessage("ERROR", "Client", "Your port is: " + this->_port);
					count_errors++;
				}
				if (this->_user.length() > 100) {
					logMessage("ERROR", "Client", "A username can only have a maximum of 100 characters and letters.");
					logMessage("ERROR", "Client", "Make sure to use a shorter username.");
					logMessage("ERROR", "Client", "Your username is: " + this->_user);
					count_errors++;
				}
				else logMessage("INFO", "Client", "Your username is valid: " + this->_user);
				if (count_errors > 0) this->_err = -1;
			}
		}
	}
}

Client::~Client() {

}

int Client::hasErrors() {
	return this->_err;
}

void Client::connect() {
	char address[] = "127.0.0.1";
	char port[] = "1234";
	const int max_length = 1024;
	try {
		// Establish connection
		boost::asio::io_context io_context;
		tcp::socket mySocket(io_context);
		tcp::resolver myResolver(io_context);
		boost::asio::connect(mySocket, myResolver.resolve(this->_address, this->_port));

		// Make a register request
		Request* myRequest = getNewRequest(REGISTER);

		// Send request to server
		boost::asio::write(mySocket, boost::asio::buffer(myRequest->serializeRequest()));

		// Delete request
		delete(myRequest);
	}
	catch (exception& e) {
		logMessage("ERROR", "Boost", "An error occured durring connection session:\n");
		cout << e.what() << endl;
		cout << endl;
		logMessage("ERROR", "Client", "Client is now terminated");
		exit(EXIT_FAILURE);
	}
}

void Client::print() {
	logMessage("INFO", "Client", "Printing client stauts:");
	logMessage("INFO", "Client", "  (-) error: " + to_string(this->_err));
	logMessage("INFO", "Client", "  (-) Address: " + this->_address);
	logMessage("INFO", "Client", "  (-) Port: " + this->_port);
	logMessage("INFO", "Client", "  (-) User: " + this->_user);
	logMessage("INFO", "Client", "  (-) File path: " + this->_path);
}

void Client::generateKeys() {
	// Randomness pool
	AutoSeededRandomPool rng;

	// Generate keys
	this->_private_Key.Initialize(rng, this->BITS);
	this->_public_key.AssignFrom(this->_private_Key);
}

string Client::getEncodedPublicKey() {
	string result;
	Base64Encoder encoder(new StringSink(result), true);
	this->_public_key.DEREncode(encoder);
	encoder.MessageEnd();
	return result;
}

Request* Client::getNewRequest(RequestType type) {
	switch (type)
	{
	case REGISTER: {
		// Create a "Name" attribute composed by 255 bytes (including null terminators). 
		array<unsigned char, 255> nameToArray;
		memset(nameToArray.data(), 0, 255);
		copy(this->_user.begin(), this->_user.end(), nameToArray.begin());

		// Define a new payload
		vector<unsigned char> newPayload(nameToArray.begin(), nameToArray.end());

		// Create and return a regiter request
		Request* result = new Request({},1,1025,newPayload);
		return result;
		break;
	}
	case PRIVATE_KEY: {
	}
	case RETRY_REGISTER: {
		break;
	}
	case SEND_FILE: {
		break;
	}

	case CRC: {
		break;
	}

	case RETRY_CRC: {
		break;
	}

	case END: {
		break;
	}

	default:
		break;
	}
}

