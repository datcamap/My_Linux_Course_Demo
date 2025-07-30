#include "button.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

ButtonState_t kbhit(void) {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}

Button_t *createButton(uint8_t buttonID, uint8_t button_GPIO)
{
    Button_t *button = (Button_t *)malloc(sizeof(Button_t));
    if (button) {
        button->buttonState = BUTTON_UNKNOWN;
        button->buttonID = buttonID;
        button->button_GPIO = button_GPIO;
    }
    return button;
}

ButtonState_t getButtonState(Button_t *const button)
{
    if (!button) {
        return BUTTON_UNKNOWN;
    }
    if (kbhit() == BUTTON_PRESSED) {
        char c = getchar(); // Read the pressed key
        if (c == (char)button->buttonID) {
            button->buttonState = BUTTON_PRESSED; // Update button state if the correct key is pressed
            printf("\nButton ---[%c]--- is pressed \n\n", (char)button->buttonID);
        }
    }
    else {
        button->buttonState = BUTTON_NOT_PRESSED; // Reset state if wrong key
    }
    return button->buttonState;
}

void destroyButton(Button_t *button)
{
    if (NULL != button) {
        free(button);
    }
}