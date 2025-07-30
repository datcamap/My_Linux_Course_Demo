#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// Define the ButtonState_t enum to represent the state of the pump
typedef enum ButtonState {
    BUTTON_PRESSED,
    BUTTON_NOT_PRESSED,
    BUTTON_UNKNOWN
}ButtonState_t;

typedef struct {
    uint8_t buttonID;   // Unique identifier for the button
    uint8_t button_GPIO; // GPIO pin number for the button
    ButtonState_t buttonState; // State of the button ref: ButtonState_t
} Button_t;

Button_t *createButton(uint8_t buttonID, uint8_t button_GPIO);
ButtonState_t getButtonState(Button_t *const button);
void destroyButton(Button_t *button);

#endif // BUTTON_H