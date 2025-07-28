#include <button.h>
#include <stdlib.h>

Button_t *createButton(uint8_t buttonID, uint8_t button_GPIO)
{
    Button_t *button = (Button_t *)malloc(sizeof(Button_t));
    if (button) {
        button->buttonState = BUTTON_NOT_PRESSED; // Initialize button state to not pressed
        button->buttonID = buttonID;
        button->button_GPIO = button_GPIO;
    }
    return button;
}

ButtonState_t getButtonState(Button_t *const button)
{
    if (!button) {
        return BUTTON_UNKNOWN; // Return not pressed if button is NULL
    }
    button->buttonState = rand() % 2; // Simulate button state change (0 or 1)
    printf("Button ID: %d, State: %s\n", button->buttonID, 
           (button->buttonState == BUTTON_PRESSED) ? "PRESSED" : "NOT PRESSED");
    return button->buttonState ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}

void destroyButton(Button_t *button)
{
    if (button) {
        free(button);
    }
}