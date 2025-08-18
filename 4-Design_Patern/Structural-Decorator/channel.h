#ifndef CHANNEL_H
#define CHANNEL_H

#include <stddef.h>
#include <stdint.h>

#ifndef CH_MAX_FRAME
#define CH_MAX_FRAME 512  /* tùy thiết bị, có thể tăng lên 1024/2048 */
#endif

/* Quy ước lỗi âm, >=0 là số byte hợp lệ */
enum {
    CH_OK = 0,
    CH_ERR = -1,
    CH_ERR_NOMEM = -2,
    CH_ERR_OVERFLOW = -3,
    CH_ERR_CRC = -4,
    CH_ERR_IO = -5
};

typedef struct Channel Channel;

typedef struct {
    /* Trả về số byte đã gửi hoặc mã lỗi âm */
    int  (*send)(Channel* self, const uint8_t* data, size_t len);

    /* Trả về số byte đã nhận (cũng ghi vào *out_len) hoặc mã lỗi âm
       Yêu cầu: bufferLength đủ chứa dữ liệu sau KHI decorator xử lý xong. */
    int  (*receive)(Channel* self, uint8_t* buffer, size_t bufferLength, size_t* out_len);
} ChannelOps;

struct Channel {
    const ChannelOps* ops;
    void*             impl;   /* trạng thái của driver/decorator */
};

/* Helper inline */
static inline int channel_send(Channel* c, const uint8_t* d, size_t n) {
    return (c && c->ops && c->ops->send) ? c->ops->send(c, d, n) : CH_ERR;
}
static inline int channel_receive(Channel* c, uint8_t* b, size_t cap, size_t* out) {
    return (c && c->ops && c->ops->receive) ? c->ops->receive(c, b, cap, out) : CH_ERR;
}

#endif /* CHANNEL_H */
