#ifndef CHANNEL_H
#define CHANNEL_H

#include <stddef.h>
#include <stdint.h>

#ifndef CH_MAX_FRAME
#define CH_MAX_FRAME 512  /* tùy thiết bị, có thể tăng lên 1024/2048 */
#endif

enum {
    CH_OK = 0,
    CH_ERR = -1,
    CH_ERR_NOMEM = -2,
    CH_ERR_OVERFLOW = -3,
    CH_ERR_CRC = -4,
    CH_ERR_IO = -5
};

typedef struct Channel Channel;

struct Channel {
    int  (*send)(Channel* self, const uint8_t* data, size_t len);
    int  (*receive)(Channel* self, uint8_t* buffer, size_t bufferLength, size_t* out_len);
    void*             impl; // Additional functionalities
};

/* Helper inline */
static inline int channel_send(Channel* c, const uint8_t* d, size_t n)
{
    return (c && c->send) ? c->send(c, d, n) : CH_ERR;
}
static inline int channel_receive(Channel* c, uint8_t* b, size_t cap, size_t* out)
{
    return (c && c->receive) ? c->receive(c, b, cap, out) : CH_ERR;
}

#endif // CHANNEL_H
