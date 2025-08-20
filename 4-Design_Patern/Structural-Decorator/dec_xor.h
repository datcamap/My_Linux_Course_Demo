#ifndef DEC_XOR_H
#define DEC_XOR_H

#include "channel.h"

typedef struct {
    Channel* inner;
    uint8_t  key;
    uint8_t  scratch[CH_MAX_FRAME];
} DecXorImpl;

void dec_xor_init(Channel* wrapper, DecXorImpl* storage, Channel* inner, uint8_t key);

#endif // DEC_XOR_H
