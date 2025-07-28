#include "main.h"
#include <stdio.h>
#include <time.h>

SystemConfig_t *systemConfig;
MoistureSensor_t *moistureSensor;
PumpControl_t *pumpController1;
Button_t *buttonMode;
Button_t *buttonPump;
LED_Controller_t *ledControllerStatus;
LED_Controller_t *ledControllerPump;
LED_Controller_t *ledControllerWarning;
time_t sensorTimeStamp = 0;
time_t imformTimeStamp = 0;
float moisture = 0.0f;

void initializeSystem()
{
    // Create system configuration
    systemConfig = createSystemConfig(SYSTEM_MODE_AUTO, 
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
    buttonMode = createButton(1, STATE_BUTTON_GPIO);
    if (NULL == buttonMode) {
        printf("Failed to create button.\n");
    }
    else {
        printf("Button created successfully.\n");
    }

    buttonPump = createButton(2, PUMP_BUTTON_GPIO);
    if (NULL == buttonPump) {
        printf("Failed to create button.\n");
    }
    else {
        printf("Button created successfully.\n");
    }

    // Create LED controller
    ledControllerStatus = createLEDController(1, STATE_LED_GPIO);
    if (NULL == ledControllerStatus) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", ledControllerStatus->ledID);
    }
    
    ledControllerPump = createLEDController(2, STATE_LED_GPIO);
    if (NULL == ledControllerStatus) {
        printf("Failed to create LED controller.\n");
    }
    else {
        printf("LED controller %d created successfully.\n", ledControllerPump->ledID);
    }
    
    ledControllerWarning = createLEDController(3, STATE_LED_GPIO);
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
    // In a real system, you would use a delay function here
    // For example: sleep(seconds);
}

void handleButtonPress()
{
    // Simulate button press handling
    if (buttonMode->buttonState == BUTTON_PRESSED) {
        if (systemConfig->mode == SYSTEM_MODE_AUTO) {
            systemConfig->mode = SYSTEM_MODE_MANUAL;
            pumpControl(pumpController1, PUMP_OFF);
            printf("Switched to manual mode.\n");
        } else {
            systemConfig->mode = SYSTEM_MODE_AUTO;
            printf("Switched to automatic mode.\n");
        }
    }

    if (buttonMode->buttonState == BUTTON_PRESSED) {
        if (systemConfig->mode == SYSTEM_MODE_MANUAL) {
            pumpControl(pumpController1, PUMP_ON); // Activate pump in manual mode
            wait(PUMP_WAIT_TIME); // Wait for pump operation
            pumpControl(pumpController1, PUMP_OFF); // Deactivate pump after wait time
            printf("Switched to manual mode.\n");
        }
    }
}

void handleLED()
{
    // Simulate LED handling based on system state
    if (systemConfig->mode == SYSTEM_MODE_AUTO) {
        setLEDState(ledControllerStatus, LED_ON); // Turn on LED in auto mode
        printf("LED is ON in automatic mode.\n");
    } else if (systemConfig->mode == SYSTEM_MODE_MANUAL) {
        setLEDState(ledControllerStatus, LED_OFF); // Turn off LED in manual mode
        printf("LED is OFF in manual mode.\n");
    }

    // Simulate LED handling based on pump state
    if (pumpController1->pumpState == PUMP_ON) {
        setLEDState(ledControllerPump, LED_ON);
        printf("Pump is activated.\n");
    } else if (pumpController1->pumpState == PUMP_OFF) {
        setLEDState(ledControllerPump, LED_OFF);
        printf("Pump is inactivate.\n");
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

        if (time(NULL) - sensorTimeStamp >= SENSOR_READ_INTERVAL) {
            sensorTimeStamp = time(NULL);
            printf("Reading moisture sensor data...\n");
            moisture = getSensorData(moistureSensor);
        }

        handleButtonPress();
        handleLED();

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
    }

    return 0; 
}