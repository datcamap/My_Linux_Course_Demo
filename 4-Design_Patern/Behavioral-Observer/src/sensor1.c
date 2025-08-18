#include "sensor1.h"
#include "stdlib.h"

SensorState_t sensor1_read(void)
{
    return rand()%2 ? SENSOR_STATE_ON : SENSOR_STATE_OFF;
}

void sensor1_init(Sensor1_t* sensor, const char sensor_id, const uint8_t sensor_gpio)
{
    if (sensor == NULL) {
        return;
    }

    sensor->id = sensor_id;
    sensor->gpio = sensor_gpio;
    sensor->read_state = sensor1_read;
    publisher_init(&sensor->base);
}
