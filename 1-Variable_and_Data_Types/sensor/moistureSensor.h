#ifndef moisture_sensor_H
#define moisture_sensor_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct moisture_sensor {
    float value;
    uint8_t id;
    uint8_t gpio;
} moisture_sensor_t;

moisture_sensor_t *create_moisture_sensor(uint8_t sensor_id, uint8_t sensor_gpio);
float get_sensor_data(moisture_sensor_t *const sensor);
void destroy_moisture_sensor(moisture_sensor_t* sensor);

#endif // moisture_sensor_H