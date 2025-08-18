#ifndef SENSOR3_H
#define SENSOR3_H

#include <stdint.h>
#include "publisher.h"

typedef struct Sensor3 Sensor3_t;

struct Sensor3 {
    char id;
    uint8_t sda_pin;
    uint8_t scl_pin;
    Publisher_t base;
    uint8_t (*read_sda)(void);
};

void sensor3_init(Sensor3_t* sensor, const char sensor_id, const uint8_t sensor_sda_pin, const uint8_t sensor_scl_pin);

#endif // SENSOR3_H
