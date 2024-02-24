#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Logger.h"

using boost::asio::ip::tcp;
using namespace std;

int main(int argc, char* argv[]) {
	
	char address[] = "127.0.0.1";
	char port[] = "1234";
	const int max_length = 1024;
	logMessage("INFO", "MyComponent", "This is a log message");
	try {
		boost::asio::io_context io_context;
		tcp::socket s(io_context);
		tcp::resolver resolver(io_context);
		boost::asio::connect(s, resolver.resolve(address,port));
		for (; ; ) {
			cout << "Enter message: ";
			char request[max_length];
			clearMessage(request, max_length);
			cin.getline(request, max_length);
			boost::asio::write(s, boost::asio::buffer(request, max_length));
			char response[max_length];
			size_t response_length = boost::asio::read(s, boost::asio::buffer(response, 19));
			response[response_length] = '\0';
			cout << "Response from server: " << response << endl;
		}
	}
	catch (exception& e) {
		"ERROR", "BoostLib", "";
	}
	
}