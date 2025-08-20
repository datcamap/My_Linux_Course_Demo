#include "dec_crc16.h"
#include <string.h>

/* CRC16-CCITT (poly 0x1021), init 0xFFFF, không reflect */
static uint16_t crc16_ccitt(const uint8_t* data, size_t len)
{
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < len; ++i) {
        crc ^= (uint16_t)data[i] << 8;
        for (int b = 0; b < 8; ++b) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

static int ccrc_send(Channel* self, const uint8_t* data, size_t len)
{
    DecCRC16Impl* st = (DecCRC16Impl*)self->impl;
    if (len + 2 > sizeof(st->scratch)) {
        return CH_ERR_OVERFLOW;
    }
    memcpy(st->scratch, data, len);
    uint16_t crc = crc16_ccitt(data, len);
    st->scratch[len]   = (uint8_t)(crc & 0xFF);
    st->scratch[len+1] = (uint8_t)(crc >> 8);
    return channel_send(st->inner, st->scratch, len + 2);
}

static int ccrc_receive(Channel* self, uint8_t* out, size_t cap, size_t* out_len)
{
    DecCRC16Impl* st = (DecCRC16Impl*)self->impl;
    size_t n = 0;
    int rc = channel_receive(st->inner, st->scratch, sizeof(st->scratch), &n);
    if (rc < 0) {
        return rc;
    }
    if (n < 2) {
        if (out_len) *out_len = 0; 
        return 0; 
    }
    size_t payload = n - 2;
    uint16_t got = (uint16_t)st->scratch[payload] | ((uint16_t)st->scratch[payload+1] << 8);
    uint16_t exp = crc16_ccitt(st->scratch, payload);
    if (got != exp) {
        return CH_ERR_CRC;
    }
    if (payload > cap) {
        return CH_ERR_OVERFLOW;
    }
    
    memcpy(out, st->scratch, payload);
    
    if (out_len) {
        *out_len = payload;
    }
    
    return (int)payload;
}

static const ChannelOps OPS = {
    .send = ccrc_send,
    .receive = ccrc_receive
};

void dec_crc16_init(Channel* wrapper, DecCRC16Impl* storage, Channel* inner)
{
    storage->inner = inner;
    wrapper->ops = &OPS;
    wrapper->impl = storage;
}
