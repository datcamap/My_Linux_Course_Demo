#ifndef DEC_CRC16_H
#define DEC_CRC16_H

#include "channel.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    Channel* inner;                 /* kênh phía dưới */
    uint8_t  scratch[CH_MAX_FRAME]; /* đệm xử lý */
} DecCRC16Impl;

void dec_crc16_init(Channel* wrapper, DecCRC16Impl* storage, Channel* inner);

#ifdef __cplusplus
}
#endif
#endif /* DEC_CRC16_H */
