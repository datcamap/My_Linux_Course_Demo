#ifndef PUMP_CONTROLLER_H
#define PUMP_CONTROLLER_H

#include <stdint.h>

typedef enum pump_state {
    PUMP_OFF,
    PUMP_ON,
    PUMP_UNKNOWN
} pump_state_t;

typedef struct pump_control {
    uint8_t id;
    uint8_t gpio;
    pump_state_t state;
} pump_control_t;

pump_control_t *create_pump_control(uint8_t pump_id, uint8_t pump_pin);
pump_state_t get_pump_state(pump_control_t *const pump);
void pump_control(pump_control_t *pump, pump_state_t pump_state_value);
void destroy_pump_control(pump_control_t *pump);

#endif // PUMP_CONTROLLER_H