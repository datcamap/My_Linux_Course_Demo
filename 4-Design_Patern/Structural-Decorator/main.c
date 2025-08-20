#include <stdio.h>
#include <string.h>
#include "channel.h"
#include "raw_loopback.h"
#include "dec_crc16.h"
#include "dec_xor.h"
#include "dec_rle.h"
#include "dec_log.h"

int main(void) {
    /* 1) Tạo raw */
    Channel raw;
    RawLoopbackImpl raw_mem;
    raw_loopback_init(&raw, &raw_mem);

    /* 2) Bọc CRC trên raw */
    Channel ch_crc;
    DecCRC16Impl crc_mem;
    dec_crc16_init(&ch_crc, &crc_mem, &raw);

    /* 3) Bọc XOR trên CRC */
    Channel ch_xor;
    DecXorImpl xor_mem;
    dec_xor_init(&ch_xor, &xor_mem, &ch_crc, 0x5A);

    /* 4) Bọc RLE trên XOR (đây là kênh app sẽ dùng) */
    Channel ch_rle;
    DecRleImpl rle_mem;
    dec_rle_init(&ch_rle, &rle_mem, &ch_xor);

    /* (Tùy chọn) quan sát: thêm log ở ngay trên raw để xem dữ liệu thực sự qua “dây” */
    Channel ch_log;
    DecLogImpl log_mem;
    dec_log_init(&ch_log, &log_mem, &raw, NULL);
    /* Nếu muốn, thay inner của CRC thành ch_log để log dưới lớp CRC:
       dec_crc16_init(&ch_crc, &crc_mem, &ch_log); */

    /* Gói tin demo: nhiều byte giống nhau để RLE hiệu quả */
    const uint8_t msg[] = { 0xAA,0xAA,0xAA,0xAA,0xAA, 0x10,0x10, 0x01,0x02,0x03, 0x10,0x10 };
    printf("App SEND %zu bytes\n", sizeof msg);

    /* Gửi qua “đầu trên cùng”: RLE -> XOR -> CRC -> RAW */
    int s = channel_send(&ch_rle, msg, sizeof msg);
    if (s < 0) { printf("send err %d\n", s); return 1; }

    /* Nhận ngược lại từ “đầu trên cùng”: RAW -> CRC -> XOR -> RLE */
    uint8_t out[CH_MAX_FRAME]; size_t got = 0;
    int r = channel_receive(&ch_rle, out, sizeof out, &got);
    if (r < 0) { printf("recv err %d\n", r); return 1; }

    printf("App RECV %zu bytes\n", got);
    int ok = (got == sizeof msg) && (memcmp(out, msg, got) == 0);
    printf("Round-trip %s\n", ok ? "OK" : "FAIL");

    /* In dữ liệu nhận để kiểm chứng */
    if (ok) {
        printf("Payload: ");
        for (size_t i = 0; i < got; ++i) printf("%02X ", out[i]);
        printf("\n");
    }
    return ok ? 0 : 2;
}
