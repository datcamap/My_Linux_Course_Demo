#include <string.h>
#include <stdlib.h>
#include "sensor_factory.h"

#ifndef SENSOR_MAX_DRIVERS
#define SENSOR_MAX_DRIVERS 16
#endif

static const SensorDriver* g_drivers[SENSOR_MAX_DRIVERS];
static size_t g_num_drivers = 0;

int sensor_register_driver(const SensorDriver* drv) {
    if (!drv || !drv->kind || !drv->create) return -1;
    if (g_num_drivers >= SENSOR_MAX_DRIVERS) return -2;
    
    for (size_t i = 0; i < g_num_drivers; ++i) {
        if (0 == strcmp(g_drivers[i]->kind, drv->kind)) return -3;
    }
    g_drivers[g_num_drivers++] = drv;
    return 0;
}

Sensor* sensor_create(const char* kind, const SensorConfig* cfg) {
    for (size_t i = 0; i < g_num_drivers; ++i) {
        if (0 == strcmp(g_drivers[i]->kind, kind)) {
            Sensor* s = g_drivers[i]->create();
            if (!s) return NULL;
            if (sensor_init(s, cfg) == SENSOR_OK) return s;
            sensor_destroy(s);
            return NULL;
        }
    }
    return NULL;
}

void sensor_destroy(Sensor* s) {
    if (!s) return;
    sensor_deinit(s);
    free(s);
}
