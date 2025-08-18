#ifndef DEC_LOG_H
#define DEC_LOG_H

#include "channel.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*log_fn_t)(const char* dir, const uint8_t* data, size_t n);

typedef struct {
    Channel* inner;
    log_fn_t logger; /* nếu NULL dùng logger mặc định */
    uint8_t  scratch[CH_MAX_FRAME];
} DecLogImpl;

void dec_log_init(Channel* wrapper, DecLogImpl* storage, Channel* inner, log_fn_t fn);

#ifdef __cplusplus
}
#endif
#endif /* DEC_LOG_H */
