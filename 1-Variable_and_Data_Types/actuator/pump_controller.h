#include <stdint.h>

// Define the PumpState_t enum to represent the state of the pump
typedef enum PumpState {
    PUMP_OFF,
    PUMP_ON,
    PUMP_UNKNOWN
} PumpState_t;

typedef struct Pump_Control {
    uint8_t pumpID;        // Unique identifier for the pump
    uint8_t pump_GPIO;     // GPIO pin number for the pump
    uint8_t pump_state;     // State of the pump ref: PumpState_t
} Pump_Control_t;

Pump_Control_t *create_pump_control(uint8_t pumpID, uint8_t pump_GPIO);
PumpState_t get_pump_state(Pump_Control_t *const pump);
void pump_control(Pump_Control_t *pump, PumpState_t state);
void destroy_pump_control(Pump_Control_t *pump);