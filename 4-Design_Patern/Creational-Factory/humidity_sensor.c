#include <stdlib.h>
#include "sensor_factory.h"

typedef struct {
    uint32_t addr;
} HumImpl;

static SensorStatus hum_init(Sensor* self, const SensorConfig* cfg) {
    HumImpl* impl = (HumImpl*)self->impl;
    impl->addr = cfg ? cfg->dev_addr : 0x40;
    return SENSOR_OK;
}
static SensorStatus hum_read(Sensor* self, float* out)
{
    (void)self;
    if (out) *out = 60.0f; // %RH giả lập
    return SENSOR_OK;
}
static void hum_deinit(Sensor* self)
{
    (void)self;
}
static const char* hum_unit(Sensor* self)
{ 
    (void)self;
    return "%RH";
}

static const SensorOps HUM_OPS = {
    .init = hum_init, 
    .read = hum_read, 
    .deinit = hum_deinit,
    .calibrate = NULL, 
    .unit = hum_unit,
};

static Sensor* hum_create(void) {
    Sensor* s = (Sensor*)malloc(sizeof(Sensor));
    HumImpl* impl = (HumImpl*)malloc(sizeof(HumImpl));
    if (!s || !impl) { free(s); free(impl); return NULL; }
    s->ops = &HUM_OPS; s->impl = impl; return s;
}

static const SensorDriver HUM_DRIVER = {
    .kind = "humidity",
    .create = hum_create
};

void humidity_driver_register(void) {
    (void)sensor_register_driver(&HUM_DRIVER);
}
