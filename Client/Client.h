#pragma once
#include <boost/asio.hpp>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "rsa.h"
#include "osrng.h"
#include "base64.h"
#include "files.h"
#include "Logger.h"
#include "Request.h"


using namespace std;
using namespace CryptoPP;
using boost::asio::ip::tcp;

enum RequestType { REGISTER, PRIVATE_KEY, RETRY_REGISTER, SEND_FILE, CRC, RETRY_CRC, END};

class Client {
	private:
		static const unsigned int KEYSIZE = 160;
		static const unsigned int BITS = 1024;
		int _err;
		string _address;
		string _port;
		string _user;
		string _path;
		RSA::PrivateKey _private_Key;
		RSA::PublicKey _public_key;
	public:
		Client();
		~Client();
		int hasErrors();
		void print();
		void connect();
		void generateKeys();
		Request* getNewRequest(RequestType type);
		string getEncodedPublicKey();
};