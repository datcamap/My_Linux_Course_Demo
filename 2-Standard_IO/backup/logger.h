#ifndef LOGGER_H
#define LOGGER_H

#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

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
    LOG_TO_FILE,
    LOG_TO_CONSOLE_AND_FILE,
} log_mode_t;

typedef struct logger_config {
    log_level_t level;
    char file_name[PATH_MAX];
    log_mode_t mode;
} logger_config_t;

typedef struct logger {
    logger_config_t config;
    void (*e) (const char *message, ...);
    void (*a) (const char *message, ...);
    void (*c) (const char *message, ...);
    void (*err) (const char *message, ...);
    void (*w) (const char *message, ...);
    void (*n) (const char *message, ...);
    void (*i) (const char *message, ...);
    void (*d) (const char *message, ...);
} logger_t;

logger_t init_logger(log_level_t log_level, const char* log_file_name, log_mode_t log_mode);
void set_log_level(log_level_t level);

#endif // LOGGER_H