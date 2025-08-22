#include "sensor_factory.h"
#include <stdio.h>

void example(void) {
    SensorConfig cfg = {.bus_id=1, .dev_addr=0x48};
    Sensor* temper_sen = sensor_create("temperature", &cfg);
    if (temper_sen) {
        float v_temper;
        if (sensor_read(temper_sen, &v_temper) == SENSOR_OK) {
            printf("Temperature is: %f%s\n", v_temper, temper_sen->unit(temper_sen));
        }
        sensor_destroy(temper_sen);
    }

    Sensor* humid_sen = sensor_create("humidity", &(SensorConfig){.bus_id=1, .dev_addr=0x40});
    if (humid_sen) {
        float v_humid;
        if (sensor_read(humid_sen, &v_humid) == SENSOR_OK) {
            printf("Humidity is: %f%s\n", v_humid, (char*)humid_sen->unit(humid_sen));
        }
        sensor_destroy(humid_sen);
    }
}

void temperature_driver_register(void);
void humidity_driver_register(void);

int main()
{
    temperature_driver_register();
    humidity_driver_register();

    example();

    return 0;
}