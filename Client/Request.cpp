#include "Request.h"

Request::Request(const array<unsigned char, 16>& clientID, unsigned char version, uint16_t code, vector<unsigned char>& payload)
{
	this->_err = 0;
	this->_clientID = clientID;
	this->_version = version;
	this->_code = code;
	this->_payloadSize = static_cast<uint32_t>(payload.size());
	this->_payload = payload;
}

vector<unsigned char> Request::serializeRequest() {
	vector<unsigned char> serializedRequest;

    // Handle clientID
    serializedRequest.insert(serializedRequest.end(), this->_clientID.begin(), this->_clientID.end());

    // Handle Version
    serializedRequest.push_back(this->_version);

    // Handle Code (little endian)
    serializedRequest.push_back(static_cast<unsigned char>(this->_code & 0xFF));
    serializedRequest.push_back(static_cast<unsigned char>((this->_code >> 8) & 0xFF));

    // Handle payloadSize (little endian)
    serializedRequest.push_back(static_cast<unsigned char>(this->_payloadSize & 0xFF));
    serializedRequest.push_back(static_cast<unsigned char>((this->_payloadSize >> 8) & 0xFF));
    serializedRequest.push_back(static_cast<unsigned char>((this->_payloadSize >> 16) & 0xFF));
    serializedRequest.push_back(static_cast<unsigned char>((this->_payloadSize >> 24) & 0xFF));

    // Handle payload
    serializedRequest.insert(serializedRequest.end(), this->_payload.begin(), this->_payload.end());

    return serializedRequest;
}

Request::~Request()
{
}