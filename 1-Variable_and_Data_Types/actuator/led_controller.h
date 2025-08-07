#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <stdint.h>

typedef enum led_state {
    LED_OFF,
    LED_ON,
    LED_UNKNOWN
} led_state_t;

typedef struct led_controller {
    uint8_t id;
    uint8_t gpio;
    led_state_t state; 
} led_controller_t;

led_controller_t *create_led_controller(uint8_t led_id, uint8_t led_gpio);
led_state_t get_led_state(led_controller_t *const led);
void set_led_state(led_controller_t *led, led_state_t led_state);
void destroy_led_controller(led_controller_t *led);

#endif // LED_CONTROLLER_H