#include "pumpController.h"
#include "moistureSensor.h"
#include "button.h"
#include "LED_Controller.h"
#include "systemConfig.h"
#include <stdio.h>
#include <time.h>

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

SystemConfig_t *systemConfig;
MoistureSensor_t *moistureSensor;
PumpControl_t *pumpController1;
Button_t *buttonMode;
Button_t *buttonPump;
LED_Controller_t *ledControllerStatus;
LED_Controller_t *ledControllerPump;
LED_Controller_t *ledControllerWarning;
time_t sensorTimeStamp = 0;
time_t informTimeStamp = 0;
time_t waitTimeStamp = 0;
float moisture = 0.0f;

void initializeSystem()
{
    // Create system configuration
    systemConfig = getSystemConfig();
    systemConfig = updateSystemConfig(SYSTEM_MODE_AUTO, 
                                       MOISTURE_THRESHOLD_MIN, 
                                       MOISTURE_THRESHOLD_MAX, 
                                       PUMP_WAIT_TIME, 
                                       SENSOR_READ_INTERVAL,
                                       INFORMING_INTERVAL);
    if (NULL == systemConfig) {
        printf("Failed to create system configuration.\n");
    }
    else {
        printf("System configuration created successfully.\n");
    }

    // Create moisture sensor
    moistureSensor = createMoistureSensor(1, MOISTURE_SENSOR_GPIO);
    if (NULL == moistureSensor) {
        printf("Failed to create moisture sensor.\n");
    }
    else {
        printf("Moisture sensor created successfully.\n");
    }

    // Create pump control
    pumpController1 = createPumpControl(1, PUMP_GPIO);
    if (NULL == pumpController1) {
        printf("Failed to create pump control.\n");
    }
    else {
        printf("Pump control created successfully.\n");
    }

    // Create button
    buttonMode = createButton((uint8_t)'m', STATE_BUTTON_GPIO);
    if (NULL == buttonMode) {
        printf("Failed to create button.\n");
    }
    else {
        printf("Button created successfully.\n");
    }

    buttonPump = createButton((uint8_t)'p', PUMP_BUTTON_GPIO);
    if (NULL == buttonPump) {
        printf("Failed to create button.\n");
    }
    else {
        printf("Button created successfully.\n");
    }

    // Create LED controller
    ledControllerStatus = createLEDController((uint8_t)'M', STATE_LED_GPIO);
    if (NULL == ledControllerStatus) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", ledControllerStatus->ledID);
    }
    
    ledControllerPump = createLEDController((uint8_t)'P', STATE_LED_GPIO);
    if (NULL == ledControllerStatus) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", ledControllerPump->ledID);
    }
    
    ledControllerWarning = createLEDController((uint8_t)'W', STATE_LED_GPIO);
    if (NULL == ledControllerStatus) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", ledControllerWarning->ledID);
    }
}

void wait(uint32_t seconds)
{
    // Simulate waiting for a specified number of seconds
    printf("Waiting for %u seconds...\n", seconds);
    waitTimeStamp = time(NULL);
    while (time(NULL) - waitTimeStamp < seconds);
}

void handleButtonPress()
{
    // Simulate button press handling
    if (getButtonState(buttonMode) == BUTTON_PRESSED) {
        if (systemConfig->mode == SYSTEM_MODE_AUTO) {
            systemConfig->mode = SYSTEM_MODE_MANUAL;
            pumpControl(pumpController1, PUMP_OFF);
            printf("Switched to manual mode.\n");
        } 
        else if (systemConfig->mode == SYSTEM_MODE_MANUAL) {
            systemConfig->mode = SYSTEM_MODE_AUTO;
            printf("Switched to automatic mode.\n");
        }
    }

    if (getButtonState(buttonPump) == BUTTON_PRESSED) {
        if (systemConfig->mode == SYSTEM_MODE_MANUAL) {
            pumpControl(pumpController1, PUMP_ON); // Activate pump in manual mode
            wait(PUMP_WAIT_TIME); // Wait for pump operation
            pumpControl(pumpController1, PUMP_OFF); // Deactivate pump after wait time
        }
    }
}

void handleLED()
{
    // Simulate LED handling based on system state
    if (systemConfig->mode == SYSTEM_MODE_AUTO) {
        setLEDState(ledControllerStatus, LED_ON); // Turn on LED in auto mode
    } else if (systemConfig->mode == SYSTEM_MODE_MANUAL) {
        setLEDState(ledControllerStatus, LED_OFF); // Turn off LED in manual mode
    }

    // Simulate LED handling based on pump state
    if (pumpController1->pumpState == PUMP_ON) {
        setLEDState(ledControllerPump, LED_ON);
    } else if (pumpController1->pumpState == PUMP_OFF) {
        setLEDState(ledControllerPump, LED_OFF);
    }
}

int main()
{
    sensorTimeStamp = time(NULL);
    printf("Current timestamp: %ld\n", sensorTimeStamp);

    initializeSystem();

    while (1)
    {
        if (time(NULL) - sensorTimeStamp >= systemConfig->sensorReadInterval) {
            sensorTimeStamp = time(NULL);
            printf("Reading moisture sensor data...\n");
            moisture = getSensorData(moistureSensor);
        }

        if (time(NULL) - informTimeStamp >= systemConfig->informingInterval) {
            informTimeStamp = time(NULL);
            printf("\n-------------- \n");
            printf("Moisture: %.2f%% \n", moisture);
            printf("Pump state: %s \n", pumpController1->pumpState == PUMP_ON ? "ON" : "OFF");
            printf("-------------- \n\n");
        }

        if (systemConfig->mode == SYSTEM_MODE_MANUAL) {
            printf("System is in manual mode. Waiting for button press...\n");
            // Here you would typically wait for a button press to change the state
            // For example: if (button->buttonState == BUTTON_PRESSED) { ... }
        }
        else if (systemConfig->mode == SYSTEM_MODE_AUTO) {
            printf("System is in automatic mode. \n");
            // Check if the moisture level is below the minimum threshold
            if (moisture < systemConfig->moistureThresholdMIN) {
                printf("Moisture level is below minimum threshold. Activating pump...\n");
                pumpControl(pumpController1, PUMP_ON); // Activate pump
            } else if (moisture > systemConfig->moistureThresholdMAX) {
                printf("Moisture level is sufficient. Pump remains off.\n");
                pumpControl(pumpController1, PUMP_OFF); // Deactivate pump
            }
        }

        handleButtonPress();
        handleLED();

        wait(1);
    }

    return 0; 
}