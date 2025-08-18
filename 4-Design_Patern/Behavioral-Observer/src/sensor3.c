#include "sensor3.h"
#include <stdlib.h>

static uint8_t sensor_read(void)
{
    return rand() % 256;
}

void sensor3_init(Sensor3_t* sensor, const char sensor_id, const uint8_t sensor_sda_pin, const uint8_t sensor_scl_pin)
{
    sensor->id = sensor_id;
    sensor->sda_pin = sensor_sda_pin;
    sensor->scl_pin = sensor_scl_pin;
    sensor->read_sda = sensor_read;
    publisher_init(&sensor->base);
}