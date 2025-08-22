#ifndef UART_BUILDER_H
#define UART_BUILDER_H

#include <stdbool.h>
#include "uart_types.h"

typedef struct UartBuilder UartBuilder;

struct UartBuilder {
    UartConfig cfg;
    char       last_error[128];
    UartBuilder* (*set_baud)(UartBuilder*, uint32_t);
    UartBuilder* (*set_parity)(UartBuilder*, UartParity);
    UartBuilder* (*set_stopbits)(UartBuilder*, UartStopBits);
    UartBuilder* (*set_databits)(UartBuilder*, UartDataBits);
    UartBuilder* (*set_flow)(UartBuilder*, UartFlow);
};

UartBuilder uart_builder_new(void);

UartBuilder* uart_preset_sensor(UartBuilder* b);
UartBuilder* uart_preset_radio(UartBuilder* b);
UartBuilder* uart_preset_modbus(UartBuilder* b);

bool uart_build(UartBuilder* b, UartConfig* out_cfg);

const char* uart_builder_error(const UartBuilder* b);

#endif // UART_BUILDER_H
