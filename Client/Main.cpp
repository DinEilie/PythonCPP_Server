#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include "Logger.h"
#include "Client.h"
#include "rsa.h"
#include "osrng.h"

using boost::asio::ip::tcp;
using namespace std;

int main(int argc, char* argv[]) {
	Client myClient;
	if (!myClient.hasErrors()) {
		myClient.generateKeys();
		myClient.connect();
	}
}