#ifndef DEC_LOG_H
#define DEC_LOG_H

#include "channel.h"

typedef void (*log_fn_t)(const char* dir, const uint8_t* data, size_t n);

typedef struct {
    Channel* inner;
    log_fn_t logger;
    uint8_t  scratch[CH_MAX_FRAME];
} DecLogImpl;

void dec_log_init(Channel* wrapper, DecLogImpl* storage, Channel* inner, log_fn_t fn);

#endif // DEC_LOG_H
