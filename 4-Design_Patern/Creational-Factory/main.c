#include "sensor_factory.h"

void example(void) {
    SensorConfig cfg = {.bus_id=1, .dev_addr=0x48};
    Sensor* t = sensor_create("temperature", &cfg);
    if (t) {
        float v;
        if (sensor_read(t, &v) == SENSOR_OK) {
            
        }
        sensor_destroy(t);
    }

    Sensor* h = sensor_create("humidity", &(SensorConfig){.bus_id=1, .dev_addr=0x40});
    if (h) {
        float v;
        sensor_read(h, &v);
        sensor_destroy(h);
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