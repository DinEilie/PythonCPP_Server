#pragma once

class Request
{
private:
	char _clientID[16];
	char _version[];
public:
	Request();
	~Request();
};

Request::Request()
{
}

Request::~Request()
{
}