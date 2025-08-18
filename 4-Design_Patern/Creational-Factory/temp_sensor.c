#include <stdlib.h>
#include "sensor_factory.h"

typedef struct {
    // trạng thái phần cứng, cache, v.v.
    uint32_t addr;
} TempImpl;

static SensorStatus temp_init(Sensor* self, const SensorConfig* cfg) {
    TempImpl* impl = (TempImpl*)self->impl;
    impl->addr = cfg ? cfg->dev_addr : 0x48;

    return SENSOR_OK;
}
static SensorStatus temp_read(Sensor* self, float* out) {
    (void)self;
    if (out) *out = 25.0f;
    return SENSOR_OK;
}
static void temp_deinit(Sensor* self)
{
    (void)self;
}
static const char* temp_unit(Sensor* self)
{
    (void)self;
    return "°C";
}

static const SensorOps TEMP_OPS = {
    .init = temp_init, 
    .read = temp_read, 
    .deinit = temp_deinit,
    .calibrate = NULL, 
    .unit = temp_unit,
};

static Sensor* temp_create(void) {
    Sensor* s = (Sensor*)malloc(sizeof(Sensor));
    TempImpl* impl = (TempImpl*)malloc(sizeof(TempImpl));
    if (!s || !impl) { free(s); free(impl); return NULL; }
    s->ops = &TEMP_OPS;
    s->impl = impl;
    return s;
}

static const SensorDriver TEMP_DRIVER = {
    .kind = "temperature",
    .create = temp_create
};

void temperature_driver_register(void) {
    (void)sensor_register_driver(&TEMP_DRIVER);
}
