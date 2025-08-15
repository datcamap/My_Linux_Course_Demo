#ifndef UART_BUILDER_H
#define UART_BUILDER_H

#include <stdbool.h>
#include "uart_types.h"

/* Builder “lắp ráp” cấu hình, có lưu lỗi gần nhất */
typedef struct UartBuilder UartBuilder;

struct UartBuilder {
    UartConfig cfg;
    char       last_error[128];
    bool       frozen; /* nếu muốn “đóng băng” sau khi build */
    UartBuilder* (*set_baud)(UartBuilder*, uint32_t);
    UartBuilder* (*set_parity)(UartBuilder*, UartParity);
    UartBuilder* (*set_stopbits)(UartBuilder*, UartStopBits);
    UartBuilder* (*set_databits)(UartBuilder*, UartDataBits);
    UartBuilder* (*set_flow)(UartBuilder*, UartFlow);
};

/* Khởi tạo với mặc định an toàn (115200, 8N1, no flow) */
UartBuilder uart_builder_new(void);

/* Presets (ví dụ thực tế) */
UartBuilder* uart_preset_sensor(UartBuilder* b);   /* 9600 8N1 */
UartBuilder* uart_preset_radio(UartBuilder* b);    /* 115200 8N1, RTS/CTS */
UartBuilder* uart_preset_modbus(UartBuilder* b);   /* 19200 8E1 */

/* Validate + xuất cấu hình cuối cùng */
bool uart_build(UartBuilder* b, UartConfig* out_cfg);

/* Lấy lỗi gần nhất (nếu build=false) */
const char* uart_builder_error(const UartBuilder* b);

#endif /* UART_BUILDER_H */
