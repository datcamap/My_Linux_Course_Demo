#include "pumpController.h"
#include "moistureSensor.h"
#include "button.h"
#include "LED_Controller.h"
#include "systemConfig.h"

#define MOISTURE_THRESHOLD_MIN 30.0f
#define MOISTURE_THRESHOLD_MAX 70.0f
#define PUMP_WAIT_TIME 5 // seconds
#define SENSOR_READ_INTERVAL 10 // seconds
#define INFORMING_INTERVAL 60 // seconds

#define MOISTURE_SENSOR_GPIO 5
#define PUMP_GPIO 6
#define STATE_BUTTON_GPIO 7
#define PUMP_BUTTON_GPIO 8
#define STATE_LED_GPIO 9
#define PUMP_LED_GPIO 10
#define WARNING_LED_GPIO 11

