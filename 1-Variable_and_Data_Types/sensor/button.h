#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdint.h>

// Define the button_state_t enum to represent the state of the pump
typedef enum button_state {
    BUTTON_PRESSED,
    BUTTON_NOT_PRESSED,
    BUTTON_UNKNOWN
}button_state_t;

typedef struct button {
    uint8_t id;
    uint8_t pin;
    button_state_t state;
} button_t;

button_t *create_button(uint8_t button_id, uint8_t button_pin);
button_state_t get_button_state(button_t *const button);
void destroy_button(button_t *button);

#endif // BUTTON_H