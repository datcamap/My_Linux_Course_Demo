#include <stdint.h>

// Define the LED_State_t enum to represent the state of the pump
typedef enum LED_State {
    LED_OFF,
    LED_ON,
    LED_UNKNOWN
} LED_State_t;

typedef struct LED_Controller {
    uint8_t ledID;        // Unique identifier for the LED
    uint8_t led_GPIO;     // GPIO pin number for the LED
    LED_State_t ledState; // State of the LED ref: LED_State_t
} LED_Controller_t;

LED_Controller_t *create_LED_controller(uint8_t ledID, uint8_t led_GPIO);
LED_State_t get_LED_state(LED_Controller_t *const led);
void set_LED_state(LED_Controller_t *led, LED_State_t state);
void destroy_LED_controller(LED_Controller_t *led);