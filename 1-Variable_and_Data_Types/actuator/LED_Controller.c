#include "LED_Controller.h"
#include <stdlib.h>
#include <stdio.h>

LED_Controller_t *createLEDController(uint8_t ledID, uint8_t led_GPIO)
{
    LED_Controller_t *led = (LED_Controller_t *)malloc(sizeof(LED_Controller_t));
    if (led) {
        led->ledID = ledID;
        led->led_GPIO = led_GPIO;
        led->ledState = LED_UNKNOWN;
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
    if (NULL != led) {
        led->ledState = state; 
        printf("LED [%c] : _[ %s ]_ \n", led->ledID,
               (state == LED_ON) ? "ON" : (state == LED_OFF) ? "OFF" : "UNKNOWN");
    }
}

void destroyLEDController(LED_Controller_t *led)
{
    if (led) {
        free(led); // Free the allocated memory for the LED controller
    }
}
