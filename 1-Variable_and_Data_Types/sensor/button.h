#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// Define the button_state_t enum to represent the state of the pump
typedef enum button_state {
    BUTTON_PRESSED,
    BUTTON_NOT_PRESSED,
    BUTTON_UNKNOWN
}button_state_t;

typedef struct {
    uint8_t button_ID;   // Unique identifier for the button
    uint8_t button_GPIO; // GPIO pin number for the button
    button_state_t button_state; // State of the button ref: button_state_t
} Button_t;

Button_t *create_button(uint8_t buttonID, uint8_t button_GPIO);
button_state_t get_button_state(Button_t *const button);
void destroy_button(Button_t *button);

#endif // BUTTON_H