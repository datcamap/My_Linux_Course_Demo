#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#define LOG_MESSAGE(level, ...)    log_message(level, __FILE__, __LINE__, __VA_ARGS__)

typedef enum {
    LOG_EMERGENCY,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} log_level_t;

typedef enum {
    LOG_TO_CONSOLE,
    LOG_TO_CONSOLE_AND_FILE,
} LogMode_t;

typedef struct logger_config {
    log_level_t log_level;
    char *log_file_name;
    uint8_t f_to_file;
} logger_config_t;

void init_logger(const char *file_name, log_level_t level, LogMode_t mode);
void log_message(log_level_t level, const char *file, const int line, const char *message, ...);
void set_log_level(log_level_t level);

#endif // LOGGER_H