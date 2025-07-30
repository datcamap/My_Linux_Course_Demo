#include "pumpController.h"
#include <stdlib.h>
#include <stdio.h>

PumpControl_t *createPumpControl(uint8_t pumpID, uint8_t pump_GPIO)
{
    PumpControl_t *pump = (PumpControl_t *)malloc(sizeof(PumpControl_t));
    if (pump) {
        pump->pumpID = pumpID;
        pump->pump_GPIO = pump_GPIO;
        pump->pumpState = PUMP_OFF; // Initialize pump state to off
    }
    return pump;
}

PumpState_t getPumpState(PumpControl_t *const pump)
{
    if (!pump) {
        return PUMP_UNKNOWN; // Return unknown state if pump is NULL
    }
    return pump->pumpState;
}

void pumpControl(PumpControl_t *pump, PumpState_t state)
{
    if (pump) {
        pump->pumpState = state; // Set the pump state
        printf("Pump ID: %d, State: %s\n", pump->pumpID,
               (state == PUMP_ON) ? "ON" : (state == PUMP_OFF) ? "OFF" : "UNKNOWN");
    }
}

void destroyPumpControl(PumpControl_t *pump)
{
    if (pump) {
        free(pump); // Free the allocated memory for the pump
    }
}