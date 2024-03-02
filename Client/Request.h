#pragma once
#include <array>
#include <vector>
#include <string>
#include "Logger.h"

using namespace std;

class Request
{
private:
	int _err;
	array<unsigned char, 16> _clientID;
	unsigned char _version;
	uint16_t _code;
	uint32_t _payloadSize;
	vector<unsigned char> _payload;
public:
	Request(const array<unsigned char, 16>& clientID, unsigned char version, uint16_t code, vector<unsigned char>& payload);
	vector<unsigned char> serializeRequest();
	~Request();
};