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
    logger_t leg = init_logger(LOG_WARNING, file_path, LOG_TO_CONSOLE_AND_FILE);
    
    // Example usage of the logger
    leg.i("This is an info message.");
    uint8_t a = 2;
    char* b = "arguments";
    leg.w("This is a warning message with %d %s.", a, b);
    leg.err("This is an error message.");
    leg.d("This is a debug message.");

    // Change log level to DEBUG
    set_log_level(LOG_DEBUG);
    leg.d("Debugging enabled.");
    leg.i("This is an info message.");

    return 0;
}