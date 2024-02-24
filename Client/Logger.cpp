#include "Logger.h"

// Reset a message with null terminator '\0'.
void clearMessage(char message[], int length) {
    for (int i = 0; i < length; i++) {
        message[i] = '\0';
    }
}

// Printing a log message
void logMessage(const string& level, const string& component, const string& message) {
    // Get current time
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Convert to local time
    tm local_time;
    localtime_s(&local_time, &now_time);

    // Format the timestamp
    ostringstream timestamp;
    timestamp << put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    // Format the log message
    string log;
    log = "[" + timestamp.str() + "] [" + level + "] [" + component + "] - " + message;

    // Output the log message
    cout << log << endl;
}