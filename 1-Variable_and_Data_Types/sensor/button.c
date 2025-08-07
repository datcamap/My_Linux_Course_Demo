#include "button.h"

/**
 * @brief Non-blocking check for keyboard input.
 *
 * Uses `select()` with zero timeout to check if a key has been pressed.
 * Does not block program execution.
 *
 * @return `BUTTON_PRESSED` if input is available on stdin,
 *         `BUTTON_NOT_PRESSED` otherwise.
 */
button_state_t kbhit(void) {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}

/**
 * @brief Initializes a button object.
 *
 * @param[in] button_id     Button identifier.
 * @param[in] button_pin    GPIO pin number.
 * @return Pointer to `button_t`, or NULL on failure.
 */
button_t *create_button(uint8_t button_id, uint8_t button_pin)
{
    button_t *button = (button_t *)malloc(sizeof(button_t));
    if (button != NULL) {
        button->state = BUTTON_UNKNOWN;
        button->id = button_id;
        button->pin = button_pin;
    }
    return button;
}

/**
 * @brief Gets the current state of the button.
 *
 * Checks if the button is pressed by reading input from stdin.
 * Updates the button state accordingly.
 *
 * @param[in] button  Pointer to the button object.
 * @return Current state of the button: `BUTTON_PRESSED`, `BUTTON_NOT_PRESSED`, or `BUTTON_UNKNOWN`.
 */
button_state_t get_button_state(button_t *const button)
{
    if (NULL == button) {
        return BUTTON_UNKNOWN;
    }
    if (kbhit() == BUTTON_PRESSED) {
        char c = getchar(); // Read the pressed key
        if (c == (char)button->id) {
            button->state = BUTTON_PRESSED; // Update button state if the correct key is pressed
            printf("\nButton ---[%c]--- is pressed \n\n", (char)button->id);
        }
    }
    else {
        button->state = BUTTON_NOT_PRESSED; // Reset state if wrong key
    }
    return button->state;
}

/**
 * @brief Destroys the button object and frees allocated memory.
 *
 * @param[in] button  Pointer to the button object to be destroyed.
 */
void destroy_button(button_t *button)
{
    if (button != NULL) {
        free(button);
    }
}