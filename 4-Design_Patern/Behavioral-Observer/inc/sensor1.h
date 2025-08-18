#ifndef SENSOR1_H
#define SENSOR1_H

#include <stdint.h>
#include "publisher.h"

typedef enum SensorState {
    SENSOR_STATE_OFF,
    SENSOR_STATE_ON
} SensorState_t;

typedef struct Sensor1 Sensor1_t;

struct Sensor1 {
    char id;
    uint8_t gpio;
    Publisher_t base;
    SensorState_t (*read_state)(void);
};

void sensor1_init(Sensor1_t* sensor, const char sensor_id, const uint8_t sensor_gpio);

#endif // SENSOR1_H
