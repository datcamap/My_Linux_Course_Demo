#include "LED_Controller.h"

LED_Controller_t *createLEDController(uint8_t ledID, uint8_t led_GPIO)
{
    LED_Controller_t *led = (LED_Controller_t *)malloc(sizeof(LED_Controller_t));
    if (led) {
        led->ledID = ledID;
        led->led_GPIO = led_GPIO;
        led->ledState = LED_OFF; // Initialize LED state to off
    }
    return led;
}

LED_State_t getLEDState(LED_Controller_t *const led)
{
    if (!led) {
        return LED_UNKNOWN; // Return unknown state if LED is NULL
    }
    return led->ledState;
}

void setLEDState(LED_Controller_t *led, LED_State_t state)
{
    if (led) {
        led->ledState = state; // Set the LED state
        // Here you would typically add code to control the GPIO pin for the LED
        // For example: digitalWrite(led->led_GPIO, (state == LED_ON) ? HIGH : LOW);
    }
}

void destroyLEDController(LED_Controller_t *led)
{
    if (led) {
        free(led); // Free the allocated memory for the LED controller
    }
}
