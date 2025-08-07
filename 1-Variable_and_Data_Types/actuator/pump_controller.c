#include "pump_controller.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Creates and initializes a pump control object.
 *
 * This function allocates memory for a `PumpControl_t` object,
 * assigns the provided parameters to the structure fields, and
 * sets the initial pump state to `PUMP_OFF`.
 *
 * @param[in]  pumpID     Identifier for the pump.
 * @param[in]  pump_GPIO  GPIO pin number used to control the pump.
 *
 * @return Pointer to the initialized `PumpControl_t` object if successful, 
 *         or NULL if memory allocation fails.
 */
pump_control_t *create_pump_control(uint8_t pumpID, uint8_t pump_GPIO)
{
    pump_control_t *pump = (pump_control_t *)malloc(sizeof(pump_control_t));
    if (pump) {
        pump->pump_ID = pumpID;
        pump->pump_GPIO = pump_GPIO;
        pump->pump_state = PUMP_OFF; // Initialize pump state to off
    }
    return pump;
}

/**
 * @brief Returns the current state of the given pump.
 *
 * @param[in]  pump  Pointer to the pump control.
 * @return Pump state, or `PUMP_UNKNOWN` if input is NULL.
 */
pump_state_t get_pump_state(pump_control_t *const pump)
{
    if (!pump) {
        return PUMP_UNKNOWN; // Return unknown state if pump is NULL
    }
    return pump->pump_state;
}

/**
 * @brief Sets the state of the given pump and prints its status.
 *
 * This function updates the pump state and prints a message indicating
 * whether the pump is ON, OFF, or in an unknown state.
 *
 * @param[in]  pump   Pointer to the pump control.
 * @param[in]  state  The desired state for the pump.
 */
void pump_control(pump_control_t *pump, pump_state_t state)
{
    if (pump) {
        pump->pump_state = state; // Set the pump state
        printf("Pump ID: %d, State: %s\n", pump->pump_ID,
               (state == PUMP_ON) ? "ON" : (state == PUMP_OFF) ? "OFF" : "UNKNOWN");
    }
}

/**
 * @brief Frees the memory allocated for the pump control.
 *
 * This function deallocates the memory used by the `PumpControl_t` object.
 *
 * @param[in]  pump  Pointer to the pump control to be destroyed.
 */
void destroy_pump_control(pump_control_t *pump)
{
    if (pump != NULL) {
        free(pump); // Free the allocated memory for the pump
    }
}