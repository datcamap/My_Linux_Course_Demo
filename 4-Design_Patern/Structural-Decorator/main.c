#include <stdio.h>
#include <string.h>
#include "channel.h"
#include "raw_loopback.h"
#include "dec_crc16.h"
#include "dec_xor.h"
#include "dec_rle.h"
#include "dec_log.h"

int main(void) {
    /* 1) Tạo raw
     * 2) Bọc CRC trên raw
     * 3) Bọc XOR trên CRC
     * 4) Bọc RLE trên XOR (đây là kênh app sẽ dùng)
     */
    Channel raw;
    RawLoopbackImpl raw_mem;
    raw_loopback_init(&raw, &raw_mem);

    Channel ch_crc;
    DecCRC16Impl crc_mem;
    dec_crc16_init(&ch_crc, &crc_mem, &raw);

    Channel ch_xor;
    DecXorImpl xor_mem;
    dec_xor_init(&ch_xor, &xor_mem, &ch_crc, 0x5A);

    Channel ch_rle;
    DecRleImpl rle_mem;
    dec_rle_init(&ch_rle, &rle_mem, &ch_xor);

    /* Gói tin demo: nhiều byte giống nhau để RLE hiệu quả */
    const uint8_t msg[] = { 
        0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,
        0x5B,0x48,0x65,0x6C,0x6C,0x6F,0x5F,0x57,0x6F,0x72,0x6C,0x64,0x5D,
        0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D,0x2D 
    };

    /* Gửi qua “đầu trên cùng”: RLE -> XOR -> CRC -> RAW */
    int s = channel_send(&ch_rle, msg, sizeof msg);
    if (s < 0) {
        printf("send err %d\n", s);
        return 1;
    }
    printf("App SENT %zu bytes\n", sizeof msg);

    /* Nhận ngược lại từ “đầu trên cùng”: RAW -> CRC -> XOR -> RLE */
    uint8_t out[CH_MAX_FRAME];
    size_t got = 0;
    if (channel_receive(&ch_rle, out, sizeof out, &got) < 0) {
        return 1;
    }
    printf("App RECV %zu bytes\n", got);

    /* In dữ liệu nhận để kiểm chứng */
    if ((got == sizeof msg) && (memcmp(out, msg, got) == 0)) {
        printf("Round-trip OK\n");
        printf("Payload: ");
        for (size_t i = 0; i < got; ++i) {
            printf("%02X ", out[i]);
        }
        printf("\n");
    }

    return 0;
}
