#include <stdlib.h>
#include "sensor_factory.h"

typedef struct {
    uint32_t addr;
} TempImpl;

static SensorStatus temp_init(Sensor* self, const SensorConfig* cfg) {
    TempImpl* impl = (TempImpl*)self->_cfg;
    impl->addr = cfg ? cfg->dev_addr : 0x48;
    return SENSOR_OK;
}
static SensorStatus temp_read(Sensor* self, float* out) {
    (void)self;
    if (out) {
        *out = (float)rand()/(float)RAND_MAX*100.0f;
    }
    return SENSOR_OK;
}
static void temp_deinit(Sensor* self)
{
    free(self->_cfg);
}
static const char* temp_unit(Sensor* self)
{
    (void)self;
    return "°C";
}

static Sensor* temp_create(void) {
    Sensor* sens = (Sensor*)malloc(sizeof(Sensor));
    SensorConfig* cfg = (SensorConfig*)malloc(sizeof(SensorConfig));
    if (!sens || !cfg) {
        free(sens);
        free(cfg);
        return NULL;
    }

    sens->_cfg = cfg;

    sens->init = temp_init;
    sens->read = temp_read;
    sens->deinit = temp_deinit;
    sens->calibrate = NULL;
    sens->unit = temp_unit;

    return sens;
}

static const SensorDriver TEMP_DRIVER = {
    .kind = "temperature",
    .create = temp_create
};

void temperature_driver_register(void) {
    (void)sensor_register_driver(&TEMP_DRIVER);
}
