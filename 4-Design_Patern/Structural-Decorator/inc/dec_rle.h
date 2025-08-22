#ifndef DEC_RLE_H
#define DEC_RLE_H

#include "channel.h"

typedef struct {
    Channel* inner;
    uint8_t  scratch[CH_MAX_FRAME];
} DecRleImpl;

void dec_rle_init(Channel* wrapper, DecRleImpl* storage, Channel* inner);

#endif // DEC_RLE_H
