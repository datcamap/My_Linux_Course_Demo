#include "sensor.h"

typedef struct {
    const char* kind;                 // "temperature", "humidity", "pressure", "light"
    Sensor*   (*create)(void);
} SensorDriver;

int     sensor_register_driver(const SensorDriver* drv);
Sensor* sensor_create(const char* kind, const SensorConfig* cfg);
void    sensor_destroy(Sensor* sens);
