#include "dec_xor.h"
#include <string.h>

static void xorin(uint8_t* p, size_t n, uint8_t key) {
    for (size_t i = 0; i < n; ++i) p[i] ^= key;
}

static int xor_send(Channel* self, const uint8_t* data, size_t len) {
    DecXorImpl* st = (DecXorImpl*)self->impl;
    if (len > sizeof(st->scratch)) return CH_ERR_OVERFLOW;
    memcpy(st->scratch, data, len);
    xorin(st->scratch, len, st->key);
    return channel_send(st->inner, st->scratch, len);
}

static int xor_receive(Channel* self, uint8_t* out, size_t cap, size_t* out_len) {
    DecXorImpl* st = (DecXorImpl*)self->impl;
    size_t n = 0;
    int rc = channel_receive(st->inner, st->scratch, sizeof(st->scratch), &n);
    if (rc < 0) return rc;
    if (n > cap) return CH_ERR_OVERFLOW;
    xorin(st->scratch, n, st->key);
    memcpy(out, st->scratch, n);
    if (out_len) *out_len = n;
    return (int)n;
}

static const ChannelOps OPS = {
    .send = xor_send,
    .receive = xor_receive
};

void dec_xor_init(Channel* wrapper, DecXorImpl* storage, Channel* inner, uint8_t key) {
    storage->inner = inner;
    storage->key = key;
    wrapper->ops = &OPS;
    wrapper->impl = storage;
}
