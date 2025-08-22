#include "dec_rle.h"
#include <string.h>

static int rle_encode(const uint8_t* in, size_t n, uint8_t* out, size_t cap)
{
    size_t oi = 0;
    for (size_t i = 0; i < n; ) {
        uint8_t v = in[i];
        size_t run = 1;
        while (i + run < n && in[i + run] == v && run < 255) {
            run++;
        }
        if (oi + 2 > cap) {
            return CH_ERR_OVERFLOW;
        }
        out[oi++] = (uint8_t)run;
        out[oi++] = v;
        i += run;
    }
    return (int)oi;
}

static int rle_decode(const uint8_t* in, size_t n, uint8_t* out, size_t cap)
{
    size_t oi = 0, i = 0;
    while (i + 1 < n) {
        uint8_t cnt = in[i++];
        uint8_t val = in[i++];
        if (oi + cnt > cap) {
            return CH_ERR_OVERFLOW;
        }
        for (uint8_t k = 0; k < cnt; ++k) {
            out[oi++] = val;
        }
    }
    if (i != n) {
        return CH_ERR; /* dữ liệu nén lẻ byte */
    }
    return (int)oi;
}

static int rle_send(Channel* self, const uint8_t* data, size_t len)
{
    DecRleImpl* st = (DecRleImpl*)self->impl;
    int enc = rle_encode(data, len, st->scratch, sizeof(st->scratch));
    if (enc < 0) return enc;
    return channel_send(st->inner, st->scratch, (size_t)enc);
}

static int rle_receive(Channel* self, uint8_t* out, size_t cap, size_t* out_len)
{
    DecRleImpl* st = (DecRleImpl*)self->impl;
    size_t n = 0;
    int rc = channel_receive(st->inner, st->scratch, sizeof(st->scratch), &n);
    if (rc < 0) {
        return rc;
    }
    int dec = rle_decode(st->scratch, n, out, cap);
    if (dec < 0) {
        return dec;
    }
    if (out_len) {
        *out_len = (size_t)dec;
    }
    return dec;
}

void dec_rle_init(Channel* wrapper, DecRleImpl* storage, Channel* inner)
{
    storage->inner = inner;
    wrapper->send = rle_send;
    wrapper->receive = rle_receive;
    wrapper->impl = storage;
}
