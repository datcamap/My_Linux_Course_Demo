#ifndef UART_TYPES_H
#define UART_TYPES_H

#include <stdint.h>

typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} UartParity;

typedef enum {
    UART_STOP_1 = 0,
    UART_STOP_2
} UartStopBits;

typedef enum {
    UART_DATABITS_7 = 7,
    UART_DATABITS_8 = 8,
    UART_DATABITS_9 = 9
} UartDataBits;

typedef enum {
    UART_FLOW_NONE = 0,
    UART_FLOW_RTSCTS
} UartFlow;

typedef struct {
    uint32_t    baud;
    UartParity  parity;
    UartStopBits stop_bits;
    UartDataBits data_bits;
    UartFlow     flow;
} UartConfig;

/* tiện in ra cho demo */
const char* uart_parity_str(UartParity p);
const char* uart_stopbits_str(UartStopBits s);
const char* uart_flow_str(UartFlow f);

#endif /* UART_TYPES_H */

