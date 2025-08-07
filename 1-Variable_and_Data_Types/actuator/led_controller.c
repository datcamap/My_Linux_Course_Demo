#include "led_controller.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Creates and initializes an LED controller object.
 *
 * This function allocates memory for an `led_controller_t` object,
 * assigns the provided parameters to the structure fields, and
 * sets the initial LED state to `LED_UNKNOWN`.
 *
 * @param[in]  led_ID     Identifier for the LED.
 * @param[in]  led_GPIO  GPIO pin number used to control the LED.
 *
 * @return Pointer to the initialized `led_controller_t` object if successful, 
 *         or NULL if memory allocation fails.
 */
led_controller_t *create_led_controller(uint8_t led_ID, uint8_t led_GPIO)
{
    led_controller_t *led = (led_controller_t *)malloc(sizeof(led_controller_t));
    if (led != NULL) {
        led->id = led_ID;
        led->gpio = led_GPIO;
        led->state = LED_UNKNOWN;
    }
    return led;
}

/**
 * @brief Returns the current state of the given LED.
 *
 * @param[in]  led  Pointer to the LED controller.
 * @return LED state, or `LED_UNKNOWN` if input is NULL.
 */
led_state_t get_led_state(led_controller_t *const led)
{
    if (!led) {
        return LED_UNKNOWN; // Return unknown state if LED is NULL
    }
    return led->led_state;
}

/**
 * @brief Sets the state of the given LED and prints its status.
 *
 * This function updates the LED state and prints a message indicating
 * whether the LED is ON, OFF, or in an unknown state.
 *
 * @param[in]  led    Pointer to the LED controller.
 * @param[in]  state  The desired state for the LED.
 */
void set_led_state(led_controller_t *led, led_state_t state)
{
    if (NULL != led) {
        led->led_state = state; 
        printf("LED [%c] : _[ %s ]_ \n", led->led_ID,
               (state == LED_ON) ? "ON" : (state == LED_OFF) ? "OFF" : "UNKNOWN");
    }
}

/**
 * @brief Frees the memory allocated for the LED controller.
 *
 * This function deallocates the memory used by the `led_controller_t` object.
 *
 * @param[in]  led  Pointer to the LED controller to be destroyed.
 */
void destroy_led_controller(led_controller_t *led)
{
    if (led) {
        free(led); // Free the allocated memory for the LED controller
    }
}
