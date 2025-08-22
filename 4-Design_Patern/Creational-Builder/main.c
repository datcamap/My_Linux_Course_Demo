#include <stdio.h>
#include "inc/uart_builder.h"

static void print_cfg(const char* title, const UartConfig* c) {
    printf("%s:\n", title);
    printf("  Baud     : %u\n", c->baud);
    printf("  Parity   : %s\n", uart_parity_str(c->parity));
    printf("  StopBits : %s\n", uart_stopbits_str(c->stop_bits));
    printf("  DataBits : %d\n", (int)c->data_bits);
    printf("  Flow     : %s\n\n", uart_flow_str(c->flow));
}

int main(void) {
    UartBuilder b1 = uart_builder_new();
    uart_preset_sensor(&b1);
    UartConfig sensor_cfg;
    if (uart_build(&b1, &sensor_cfg)) {
        print_cfg("SENSOR UART", &sensor_cfg);
    } else {
        printf("Build sensor failed: %s\n", uart_builder_error(&b1));
    }

    UartBuilder b2 = uart_builder_new();
    uart_preset_radio(&b2);
    UartConfig radio_cfg;
    if (uart_build(&b2, &radio_cfg)) {
        print_cfg("RADIO UART", &radio_cfg);
    } else {
        printf("Build radio failed: %s\n", uart_builder_error(&b2));
    }

    /* Error (9 data bits + parity) */
    UartBuilder b3 = uart_builder_new();
    b3.set_baud(&b3, 57600);
    b3.set_databits(&b3, UART_DATABITS_9);
    b3.set_parity(&b3, UART_PARITY_EVEN);
    UartConfig bad_cfg;
    if (!uart_build(&b3, &bad_cfg)) {
        printf("Build custom failed as expected: %s\n", uart_builder_error(&b3));
    }

    /* Typical modbus configuration (19200 8E1) */
    UartBuilder b4 = uart_builder_new();
    uart_preset_modbus(&b4);
    UartConfig modbus_cfg;
    if (uart_build(&b4, &modbus_cfg)) {
        print_cfg("MODBUS UART", &modbus_cfg);
    }

    return 0;
}
