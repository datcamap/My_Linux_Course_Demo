#ifndef SENSOR2_H
#define SENSOR2_H

#include <stdint.h>
#include "publisher.h"

typedef struct Sensor2 Sensor2_t;

struct Sensor2 {
    char id;
    uint8_t gpio;
    uint32_t baud_rate;
    Publisher_t base;
    int (*read_data)(void);
};

void sensor2_init(Sensor2_t* sensor, const char sensor_id, const uint8_t sensor_gpio, const uint32_t sensor_baud_rate);

#endif // SENSOR2_H
