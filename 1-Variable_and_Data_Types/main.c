#include "pump_controller.h"
#include "moistureSensor.h"
#include "button.h"
#include "led_controller.h"
#include "system_config.h"
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define MOISTURE_THRESHOLD_MIN 30.0f
#define MOISTURE_THRESHOLD_MAX 70.0f

#define SECOND(x) (x) // Placeholder for time conversion, replace with actual implementation if needed

#define PUMP_WAIT_TIME          (SECOND(5))
#define SENSOR_READ_INTERVAL    (SECOND(10))
#define INFORMING_INTERVAL      (SECOND(6))

#define GPIO(x) (x) // Placeholder for GPIO pin definition  

#define MOISTURE        (GPIO(5))   // Moiture sensor GPIO pin
#define PUMP            (GPIO(6))   // Pump control GPIO pin
#define STATE_BUTTON    (GPIO(7))   // Button to switch system mode
#define PUMP_BUTTON     (GPIO(8))   // Button to turn pump on/ off in manual mode
#define STATE_LED       (GPIO(9))   // LED to inform system current mode
#define PUMP_LED        (GPIO(10))  // LED to indicate pump activation state
#define WARNING_LED     (GPIO(11))  // LED warning in case of errors occur

system_config_t *sys_config = NULL;
moisture_sensor_t *moist_sensor = NULL;
pump_control_t *pump_ctrl_1 = NULL;
button_t *button_status = NULL;
button_t *button_pump = NULL;
led_controller_t *led_status = NULL;
led_controller_t *led_pump = NULL;
led_controller_t *led_warning = NULL;
time_t sensor_time_stamp = 0;
time_t inform_time_stamp = 0;
time_t wait_time_stamp = 0;
float moisture = 0.0f;

// abcd

void initialize_system()
{
    // Create system configuration
    system_config = get_system_config();
    system_config = update_system_config(system_mode_AUTO, 
                                       MOISTURE_THRESHOLD_MIN, 
                                       MOISTURE_THRESHOLD_MAX, 
                                       PUMP_WAIT_TIME, 
                                       SENSOR_READ_INTERVAL,
                                       INFORMING_INTERVAL);
    if (NULL == system_config) {
        printf("Failed to create system configuration.\n");
    }
    else {
        printf("System configuration created successfully.\n");
    }

    // Create moisture sensor
    moisture_sensor = create_moisture_sensor(1, moisture_sensor_GPIO);
    if (NULL == moisture_sensor) {
        printf("Failed to create moisture sensor.\n");
    }
    else {
        printf("Moisture sensor created successfully.\n");
    }

    // Create pump control
    pump_ctrl_1 = create_pump_control(1, PUMP_GPIO);
    if (NULL == pump_ctrl_1) {
        printf("Failed to create pump control.\n");
    }
    else {
        printf("Pump control created successfully.\n");
    }

    // Create button
    button_Mode = create_button((uint8_t)'m', STATE_BUTTON_GPIO);
    if (NULL == button_Mode) {
        printf("Failed to create button.\n");
    }
    else {
        printf("Button created successfully.\n");
    }

    button_Pump = create_button((uint8_t)'p', PUMP_BUTTON_GPIO);
    if (NULL == button_Pump) {
        printf("Failed to create button.\n");
    }
    else {
        printf("Button created successfully.\n");
    }

    // Create LED controller
    led_status = create_led_controller((uint8_t)'M', STATE_LED_GPIO);
    if (NULL == led_status) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", led_status->led_ID);
    }
    
    led_pump = create_led_controller((uint8_t)'P', STATE_LED_GPIO);
    if (NULL == led_status) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", led_pump->led_ID);
    }
    
    led_warning = create_led_controller((uint8_t)'W', STATE_LED_GPIO);
    if (NULL == led_status) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", led_warning->led_ID);
    }
}

void wait(uint32_t seconds)
{
    // Simulate waiting for a specified number of seconds
    printf("Waiting for %u seconds...\n", seconds);
    wait_time_stamp = time(NULL);
    while (time(NULL) - wait_time_stamp < seconds);
}

void* handle_button_press(void *arg)
{
    while (1) {
        // Simulate button press handling
        if (get_button_state(button_Mode) == BUTTON_PRESSED) {
            if (system_config->mode == system_mode_AUTO) {
                system_config->mode = system_mode_MANUAL;
                pump_control(pump_ctrl_1, PUMP_OFF);
                printf("Switched to [MANUAL] mode.\n");
            } 
            else if (system_config->mode == system_mode_MANUAL) {
                system_config->mode = system_mode_AUTO;
                printf("Switched to [AUTOMATIC] mode.\n");
            }
        }

        if (get_button_state(button_Pump) == BUTTON_PRESSED) {
            if (system_config->mode == system_mode_MANUAL) {
                pump_control(pump_ctrl_1, PUMP_ON); // Activate pump in manual mode
                wait(PUMP_WAIT_TIME); // Wait for pump operation
                pump_control(pump_ctrl_1, PUMP_OFF); // Deactivate pump after wait time
            }
        }
    }
}

void handle_LED()
{
    // Simulate LED handling based on system state
    if (sys_config->mode == system_mode_AUTO) {
        set_led_state(led_status, LED_ON); // Turn on LED in auto mode
    } else if (sys_config->mode == system_mode_MANUAL) {
        set_led_state(led_status, LED_OFF); // Turn off LED in manual mode
    }

    // Simulate LED handling based on pump state
    if (pump_ctrl_1->state == PUMP_ON) {
        set_led_state(led_pump, LED_ON);
    } else if (pump_ctrl_1->state == PUMP_OFF) {
        set_led_state(led_pump, LED_OFF);
    }
}

void automatic_mode()
{
    if (moisture < sys_config->moisture_threshold_MIN) {
        printf("Moisture level is below minimum threshold. Activating pump...\n");
        pump_control(pump_ctrl_1, PUMP_ON); // Activate pump
    } else if (moisture > system_config->moisture_threshold_MAX) {
        printf("Moisture level is sufficient. Pump remains off.\n");
        pump_control(pump_ctrl_1, PUMP_OFF); // Deactivate pump
    }
}

int main()
{
    sensor_time_stamp = time(NULL);
    printf("Current timestamp: %ld\n", sensor_time_stamp);

    initialize_system();
    pthread_t thread;
    pthread_create(&thread, NULL, handle_button_press, NULL);

    while (1)
    {
        if (time(NULL) - sensor_time_stamp >= sys_config->reading_interval) {
            sensor_time_stamp = time(NULL);
            printf("Reading moisture sensor data...\n");
            moisture = get_sensor_data(moist_sensor);
        }

        if (time(NULL) - inform_time_stamp >= sys_config->informing_interval) {
            inform_time_stamp = time(NULL);
            printf("\n-------------- \n");
            printf("Moisture: %.2f%% \n", moisture);
            printf("Pump state: %s \n", pump_ctrl_1->state == PUMP_ON ? "ON" : "OFF");
            printf("-------------- \n\n");
        }

        if (sys_config->mode == system_mode_MANUAL) {
            printf("System is in manual mode. Waiting for button press...\n");
        }
        else if (sys_config->mode == system_mode_AUTO) {
            printf("System is in automatic mode. \n");
            automatic_mode();
        }

        handle_LED();

        wait(1);
    }

    pthread_join(thread, NULL);

    return 0; 
}