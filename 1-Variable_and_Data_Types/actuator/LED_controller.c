#include "LED_controller.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Creates and initializes an LED controller object.
 *
 * This function allocates memory for an `LED_Controller_t` object,
 * assigns the provided parameters to the structure fields, and
 * sets the initial LED state to `LED_UNKNOWN`.
 *
 * @param[in]  ledID     Identifier for the LED.
 * @param[in]  led_GPIO  GPIO pin number used to control the LED.
 *
 * @return Pointer to the initialized `LED_Controller_t` object if successful, 
 *         or NULL if memory allocation fails.
 */
LED_Controller_t *create_LED_controller(uint8_t ledID, uint8_t led_GPIO)
{
    LED_Controller_t *led = (LED_Controller_t *)malloc(sizeof(LED_Controller_t));
    if (led) {
        led->ledID = ledID;
        led->led_GPIO = led_GPIO;
        led->ledState = LED_UNKNOWN;
    }
    return led;
}

/**
 * @brief Returns the current state of the given LED.
 *
 * @param[in]  led  Pointer to the LED controller.
 * @return LED state, or `LED_UNKNOWN` if input is NULL.
 */
LED_State_t get_LED_state(LED_Controller_t *const led)
{
    if (!led) {
        return LED_UNKNOWN; // Return unknown state if LED is NULL
    }
    return led->ledState;
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
void set_LED_state(LED_Controller_t *led, LED_State_t state)
{
    if (NULL != led) {
        led->ledState = state; 
        printf("LED [%c] : _[ %s ]_ \n", led->ledID,
               (state == LED_ON) ? "ON" : (state == LED_OFF) ? "OFF" : "UNKNOWN");
    }
}

/**
 * @brief Frees the memory allocated for the LED controller.
 *
 * This function deallocates the memory used by the `LED_Controller_t` object.
 *
 * @param[in]  led  Pointer to the LED controller to be destroyed.
 */
void destroy_LED_controller(LED_Controller_t *led)
{
    if (led) {
        free(led); // Free the allocated memory for the LED controller
    }
}
