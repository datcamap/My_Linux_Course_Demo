#include "sensor2.h"
#include <stdlib.h>

static int sensor_read(void)
{
    return rand() % 100;
}

void sensor2_init(Sensor2_t* sensor, const char sensor_id, const uint8_t sensor_gpio, const uint32_t sensor_baud_rate)
{
    sensor->id = sensor_id;
    sensor->gpio = sensor_gpio;
    sensor->baud_rate = sensor_baud_rate;
    sensor->read_data = sensor_read;
    publisher_init(&sensor->base);
}