#define _GNU_SOURCE
#include "logger.h"
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <limits.h>

int main() 
{
    // Get the absolute path of the executable
    char exe_path[PATH_MAX];
    char file_path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0';
        snprintf(file_path, sizeof(file_path), "%s/%s", dirname(exe_path), "app.log");
    } else {
        perror("readlink");
    }

    // Initialize the logger with a specific log file, log level, and mode
    init_logger(file_path, LOG_WARNING, LOG_TO_CONSOLE_AND_FILE);

    // Example usage of the logger
    LOG_MESSAGE(LOG_INFO, "This is an info message.");
    LOG_MESSAGE(LOG_WARNING, "This is a warning message.");
    LOG_MESSAGE(LOG_ERROR, "This is an error message.");
    LOG_MESSAGE(LOG_DEBUG, "This is a debug message.");

    // Change log level to DEBUG
    set_logLevel(LOG_DEBUG);
    LOG_MESSAGE(LOG_DEBUG, "Debugging enabled.");

    return 0;
}