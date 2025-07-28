#include <stdint.h>

// Define the PumpState_t enum to represent the state of the pump
typedef enum PumpState {
    PUMP_OFF,
    PUMP_ON,
    PUMP_UNKNOWN
} PumpState_t;

typedef struct PumpControl {
    uint8_t pumpID;        // Unique identifier for the pump
    uint8_t pump_GPIO;     // GPIO pin number for the pump
    uint8_t pumpState;     // State of the pump ref: PumpState_t
} PumpControl_t;

PumpControl_t *createPumpControl(uint8_t pumpID, uint8_t pump_GPIO);
PumpState_t getPumpState(PumpControl_t *const pump);
void pumpControl(PumpControl_t *pump, PumpState_t state);
void destroyPumpControl(PumpControl_t *pump);