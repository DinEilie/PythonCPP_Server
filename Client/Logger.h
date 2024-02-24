#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Reset a message with null terminator '\0'.
void clearMessage(char message[], int length);

// Printing a log message
void logMessage(const string& level, const string& component, const string& message);
