#include "raw_loopback.h"
#include <string.h>

static size_t fifo_free(RawLoopbackImpl* q)
{
    if (q->tail >= q->head) return CH_MAX_FRAME - (q->tail - q->head);
    return q->head - q->tail;
}
static size_t fifo_size(RawLoopbackImpl* q)
{
    if (q->tail >= q->head) return q->tail - q->head;
    return CH_MAX_FRAME - (q->head - q->tail);
}

static int raw_send(Channel* self, const uint8_t* data, size_t len)
{
    RawLoopbackImpl* q = (RawLoopbackImpl*)self->impl;
    if (len > fifo_free(q)) {
        return CH_ERR_OVERFLOW;
    }
    for (size_t i = 0; i < len; ++i) {
        q->buf[q->tail] = data[i];
        q->tail = (q->tail + 1) % CH_MAX_FRAME;
    }
    return (int)len;
}

static int raw_receive(Channel* self, uint8_t* buffer, size_t cap, size_t* out_len)
{
    RawLoopbackImpl* q = (RawLoopbackImpl*)self->impl;
    size_t n = fifo_size(q);
    if (n == 0) { if (out_len) *out_len = 0; return 0; }  /* không có dữ liệu */
    if (n > cap) return CH_ERR_OVERFLOW;
    for (size_t i = 0; i < n; ++i) {
        buffer[i] = q->buf[q->head];
        q->head = (q->head + 1) % CH_MAX_FRAME;
    }
    if (out_len) *out_len = n;
    return (int)n;
}

void raw_loopback_init(Channel* ch, RawLoopbackImpl* storage)
{
    storage->head = storage->tail = 0;
    
    ch->send = raw_send;
    ch->receive = raw_receive;
    ch->impl = storage;
}
