#ifndef DEC_CRC16_H
#define DEC_CRC16_H

#include "channel.h"

typedef struct {
    Channel* inner;
    uint8_t  scratch[CH_MAX_FRAME];
} DecCRC16Impl;

void dec_crc16_init(Channel* wrapper, DecCRC16Impl* storage, Channel* inner);

#endif // DEC_CRC16_H
