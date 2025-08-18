#include "dec_log.h"
#include <stdio.h>
#include <string.h>

static void default_logger(const char* dir, const uint8_t* data, size_t n) {
    printf("[LOG ] %s %zu bytes: ", dir, n);
    size_t show = n < 8 ? n : 8;
    for (size_t i = 0; i < show; ++i) printf("%02X ", data[i]);
    if (n > show) printf("...");
    printf("\n");
}

static int log_send(Channel* self, const uint8_t* data, size_t len) {
    DecLogImpl* st = (DecLogImpl*)self->impl;
    (st->logger ? st->logger : default_logger)("TX", data, len);
    return channel_send(st->inner, data, len);
}

static int log_receive(Channel* self, uint8_t* out, size_t cap, size_t* out_len) {
    DecLogImpl* st = (DecLogImpl*)self->impl;
    size_t n = 0;
    int rc = channel_receive(st->inner, st->scratch, sizeof(st->scratch), &n);
    if (rc < 0) return rc;
    (st->logger ? st->logger : default_logger)("RX(low)", st->scratch, n);
    if (n > cap) return CH_ERR_OVERFLOW;
    memcpy(out, st->scratch, n);
    if (out_len) *out_len = n;
    return (int)n;
}

static const ChannelOps OPS = {
    .send = log_send,
    .receive = log_receive
};

void dec_log_init(Channel* wrapper, DecLogImpl* storage, Channel* inner, log_fn_t fn) {
    storage->inner = inner;
    storage->logger = fn;
    wrapper->ops = &OPS;
    wrapper->impl = storage;
}
