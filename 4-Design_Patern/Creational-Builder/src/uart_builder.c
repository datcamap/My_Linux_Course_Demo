#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/uart_builder.h"

static UartBuilder* uart_set_baud(UartBuilder* b, uint32_t baud);
static UartBuilder* uart_set_parity(UartBuilder* b, UartParity parity);
static UartBuilder* uart_set_stopbits(UartBuilder* b, UartStopBits stop_bits);
static UartBuilder* uart_set_databits(UartBuilder* b, UartDataBits data_bits);
static UartBuilder* uart_set_flow(UartBuilder* b, UartFlow flow);

/* ---------- helpers stringify ---------- */
const char* uart_parity_str(UartParity p) {
    switch (p) {
    case UART_PARITY_NONE: return "None";
    case UART_PARITY_EVEN: return "Even";
    case UART_PARITY_ODD:  return "Odd";
    default: return "?";
    }
}
const char* uart_stopbits_str(UartStopBits s) {
    switch (s) {
    case UART_STOP_1: return "1";
    case UART_STOP_2: return "2";
    default: return "?";
    }
}
const char* uart_flow_str(UartFlow f) {
    switch (f) {
    case UART_FLOW_NONE:  return "None";
    case UART_FLOW_RTSCTS:return "RTS/CTS";
    default: return "?";
    }
}

/* ---------- defaults ---------- */
#define UART_DEFAULT_BAUD      115200u
#define UART_DEFAULT_PARITY    UART_PARITY_NONE
#define UART_DEFAULT_STOP      UART_STOP_1
#define UART_DEFAULT_DATABITS  UART_DATABITS_8
#define UART_DEFAULT_FLOW      UART_FLOW_NONE

static void set_error(UartBuilder* b, const char* msg) {
    if (!b) return;
    strncpy(b->last_error, msg, sizeof(b->last_error)-1);
    b->last_error[sizeof(b->last_error)-1] = '\0';
}

UartBuilder uart_builder_new(void) {
    UartBuilder b;
    b.cfg.baud      = UART_DEFAULT_BAUD;
    b.cfg.parity    = UART_DEFAULT_PARITY;
    b.cfg.stop_bits = UART_DEFAULT_STOP;
    b.cfg.data_bits = UART_DEFAULT_DATABITS;
    b.cfg.flow      = UART_DEFAULT_FLOW;
    b.last_error[0] = '\0';
    b.set_baud = uart_set_baud;
    b.set_parity = uart_set_parity;
    b.set_stopbits = uart_set_stopbits;
    b.set_databits = uart_set_databits;
    b.set_flow = uart_set_flow;
    return b;
}

/* ---------- fluent setters ---------- */
static UartBuilder* uart_set_baud(UartBuilder* b, uint32_t baud) {
    if (!b) {
        return NULL;
    }
    b->cfg.baud = baud;
    return b;
}
static UartBuilder* uart_set_parity(UartBuilder* b, UartParity parity) {
    if (!b) {
        return NULL;
    }
    b->cfg.parity = parity;
    return b;
}
static UartBuilder* uart_set_stopbits(UartBuilder* b, UartStopBits stop_bits) {
    if (!b) {
        return NULL;
    }
    b->cfg.stop_bits = stop_bits;
    return b;
}
static UartBuilder* uart_set_databits(UartBuilder* b, UartDataBits data_bits) {
    if (!b) {
        return NULL;
    }
    b->cfg.data_bits = data_bits;
    return b;
}
static UartBuilder* uart_set_flow(UartBuilder* b, UartFlow flow) {
    if (!b) return NULL;
    b->cfg.flow = flow;
    return b;
}

/* ---------- presets aka directors ---------- */
UartBuilder* uart_preset_sensor(UartBuilder* b) {
    if (!b) return NULL;
    return b->set_baud(b, 9600) \
           ->set_parity(b, UART_PARITY_NONE) \
           ->set_stopbits(b, UART_STOP_1) \
           ->set_databits(b, UART_DATABITS_8) \
           ->set_flow(b, UART_FLOW_NONE);
}

UartBuilder* uart_preset_radio(UartBuilder* b) {
    if (!b) return NULL;
    return b->set_baud(b, 115200) \
           ->set_parity(b, UART_PARITY_NONE) \
           ->set_stopbits(b, UART_STOP_1) \
           ->set_databits(b, UART_DATABITS_8) \
           ->set_flow(b, UART_FLOW_RTSCTS);
}

UartBuilder* uart_preset_modbus(UartBuilder* b) {
    if (!b) return NULL;
    return b->set_baud(b, 19200)\
           ->set_parity(b, UART_PARITY_EVEN) \
           ->set_stopbits(b, UART_STOP_1) \
           ->set_databits(b, UART_DATABITS_8) \
           ->set_flow(b, UART_FLOW_NONE);
}

/* ---------- validation rules ---------- 
   for hardware specifics constrain */
static bool validate(const UartConfig* c, char* err, size_t errsz) {
    if (c->baud < 110 || c->baud > 3000000u) {
        snprintf(err, errsz, "baud %u out of range [110..3000000]", c->baud);
        return false;
    }
    if (c->data_bits == UART_DATABITS_9 && c->parity != UART_PARITY_NONE) {
        snprintf(err, errsz, "9 data bits with parity is not supported (portable rule)");
        return false;
    }
    if (!(c->stop_bits == UART_STOP_1 || c->stop_bits == UART_STOP_2)) {
        snprintf(err, errsz, "invalid stop bits");
        return false;
    }
    
    return true;
}

bool uart_build(UartBuilder* b, UartConfig* out_cfg) {
    if (!b || !out_cfg) return false;
    char err[128] = {0};
    if (!validate(&b->cfg, err, sizeof(err))) {
        set_error(b, err);
        return false;
    }
    *out_cfg = b->cfg;
    return true;
}

const char* uart_builder_error(const UartBuilder* b) {
    if (!b) return "builder is NULL";
    return b->last_error[0] ? b->last_error : "no error";
}
