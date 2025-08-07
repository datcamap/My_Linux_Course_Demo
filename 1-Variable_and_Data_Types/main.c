#include "pump_controller.h"
#include "moistureSensor.h"
#include "button.h"
#include "LED_controller.h"
#include "system_config.h"
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define MOISTURE_THRESHOLD_MIN 30.0f
#define MOISTURE_THRESHOLD_MAX 70.0f
#define PUMP_WAIT_TIME 5 // seconds
#define SENSOR_READ_INTERVAL 10 // seconds
#define INFORMING_INTERVAL 6 // seconds

#define MOISTURE_SENSOR_GPIO 5
#define PUMP_GPIO 6
#define STATE_BUTTON_GPIO 7
#define PUMP_BUTTON_GPIO 8
#define STATE_LED_GPIO 9
#define PUMP_LED_GPIO 10
#define WARNING_LED_GPIO 11

System_Config_t *system_Config = NULL;
Moisture_Sensor_t *moisture_Sensor = NULL;
Pump_Control_t *pump_Controller1 = NULL;
Button_t *button_Mode = NULL;
Button_t *button_Pump = NULL;
LED_Controller_t *led_Controller_Status = NULL;
LED_Controller_t *led_Controller_Pump = NULL;
LED_Controller_t *led_Controller_Warning = NULL;
time_t sensor_Time_Stamp = 0;
time_t inform_Time_Stamp = 0;
time_t wait_Time_Stamp = 0;
float moisture = 0.0f;

void initialize_system()
{
    // Create system configuration
    system_Config = get_system_config();
    system_Config = update_system_config(SYSTEM_MODE_AUTO, 
                                       MOISTURE_THRESHOLD_MIN, 
                                       MOISTURE_THRESHOLD_MAX, 
                                       PUMP_WAIT_TIME, 
                                       SENSOR_READ_INTERVAL,
                                       INFORMING_INTERVAL);
    if (NULL == system_Config) {
        printf("Failed to create system configuration.\n");
    }
    else {
        printf("System configuration created successfully.\n");
    }

    // Create moisture sensor
    moisture_Sensor = create_moisture_sensor(1, MOISTURE_SENSOR_GPIO);
    if (NULL == moisture_Sensor) {
        printf("Failed to create moisture sensor.\n");
    }
    else {
        printf("Moisture sensor created successfully.\n");
    }

    // Create pump control
    pump_Controller1 = create_pump_control(1, PUMP_GPIO);
    if (NULL == pump_Controller1) {
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
    led_Controller_Status = create_LED_controller((uint8_t)'M', STATE_LED_GPIO);
    if (NULL == led_Controller_Status) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", led_Controller_Status->led_ID);
    }
    
    led_Controller_Pump = create_LED_controller((uint8_t)'P', STATE_LED_GPIO);
    if (NULL == led_Controller_Status) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", led_Controller_Pump->led_ID);
    }
    
    led_Controller_Warning = create_LED_controller((uint8_t)'W', STATE_LED_GPIO);
    if (NULL == led_Controller_Status) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", led_Controller_Warning->led_ID);
    }
}

void wait(uint32_t seconds)
{
    // Simulate waiting for a specified number of seconds
    printf("Waiting for %u seconds...\n", seconds);
    wait_Time_Stamp = time(NULL);
    while (time(NULL) - wait_Time_Stamp < seconds);
}

void* handle_button_press(void *arg)
{
    while (1) {
        // Simulate button press handling
        if (get_button_state(button_Mode) == BUTTON_PRESSED) {
            if (system_Config->mode == SYSTEM_MODE_AUTO) {
                system_Config->mode = SYSTEM_MODE_MANUAL;
                pump_control(pump_Controller1, PUMP_OFF);
                printf("Switched to [MANUAL] mode.\n");
            } 
            else if (system_Config->mode == SYSTEM_MODE_MANUAL) {
                system_Config->mode = SYSTEM_MODE_AUTO;
                printf("Switched to [AUTOMATIC] mode.\n");
            }
        }

        if (get_button_state(button_Pump) == BUTTON_PRESSED) {
            if (system_Config->mode == SYSTEM_MODE_MANUAL) {
                pump_control(pump_Controller1, PUMP_ON); // Activate pump in manual mode
                wait(PUMP_WAIT_TIME); // Wait for pump operation
                pump_control(pump_Controller1, PUMP_OFF); // Deactivate pump after wait time
            }
        }
    }
}

void handle_LED()
{
    // Simulate LED handling based on system state
    if (system_Config->mode == SYSTEM_MODE_AUTO) {
        set_LED_state(led_Controller_Status, LED_ON); // Turn on LED in auto mode
    } else if (system_Config->mode == SYSTEM_MODE_MANUAL) {
        set_LED_state(led_Controller_Status, LED_OFF); // Turn off LED in manual mode
    }

    // Simulate LED handling based on pump state
    if (pump_Controller1->pump_state == PUMP_ON) {
        set_LED_state(led_Controller_Pump, LED_ON);
    } else if (pump_Controller1->pump_state == PUMP_OFF) {
        set_LED_state(led_Controller_Pump, LED_OFF);
    }
}

void automatic_mode()
{
    if (moisture < system_Config->moisture_threshold_MIN) {
        printf("Moisture level is below minimum threshold. Activating pump...\n");
        pump_control(pump_Controller1, PUMP_ON); // Activate pump
    } else if (moisture > system_Config->moisture_threshold_MAX) {
        printf("Moisture level is sufficient. Pump remains off.\n");
        pump_control(pump_Controller1, PUMP_OFF); // Deactivate pump
    }
}

int main()
{
    sensor_Time_Stamp = time(NULL);
    printf("Current timestamp: %ld\n", sensor_Time_Stamp);

    initialize_system();
    pthread_t thread;
    pthread_create(&thread, NULL, handle_button_press, NULL);

    while (1)
    {
        if (time(NULL) - sensor_Time_Stamp >= system_Config->sensor_read_interval) {
            sensor_Time_Stamp = time(NULL);
            printf("Reading moisture sensor data...\n");
            moisture = get_sensor_data(moisture_Sensor);
        }

        if (time(NULL) - inform_Time_Stamp >= system_Config->informing_interval) {
            inform_Time_Stamp = time(NULL);
            printf("\n-------------- \n");
            printf("Moisture: %.2f%% \n", moisture);
            printf("Pump state: %s \n", pump_Controller1->pump_state == PUMP_ON ? "ON" : "OFF");
            printf("-------------- \n\n");
        }

        if (system_Config->mode == SYSTEM_MODE_MANUAL) {
            printf("System is in manual mode. Waiting for button press...\n");
        }
        else if (system_Config->mode == SYSTEM_MODE_AUTO) {
            printf("System is in automatic mode. \n");
            automatic_mode();
        }

        handle_LED();

        wait(1);
    }

    pthread_join(thread, NULL);

    return 0; 
}