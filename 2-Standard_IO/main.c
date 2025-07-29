#include "logger.h"
#include <stdio.h>

int main() 
{
    // Initialize the logger with a specific log file, log level, and mode
    initLogger("app.log", LOG_DEBUG, LOG_TO_CONSOLE_AND_FILE);

    // Example usage of the logger
    LOG_MESSAGE(LOG_INFO, "This is an info message.");
    LOG_MESSAGE(LOG_WARNING, "This is a warning message.");
    LOG_MESSAGE(LOG_ERROR, "This is an error message.");
    LOG_MESSAGE(LOG_DEBUG, "This is a debug message.");

    // Change log level to DEBUG
    setLogLevel(LOG_DEBUG);
    LOG_MESSAGE(LOG_DEBUG, "Debugging enabled.");

    return 0;
}