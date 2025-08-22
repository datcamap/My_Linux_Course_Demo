#ifndef RAW_LOOPBACK_H
#define RAW_LOOPBACK_H

#include "channel.h"

typedef struct {
    uint8_t buf[CH_MAX_FRAME];
    size_t  head, tail; /* FIFO đơn giản */
} RawLoopbackImpl;

void raw_loopback_init(Channel* ch, RawLoopbackImpl* storage);

#endif // RAW_LOOPBACK_H
