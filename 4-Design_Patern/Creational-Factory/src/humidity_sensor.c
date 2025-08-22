#include <stdlib.h>
#include "sensor_factory.h"

typedef struct {
    uint32_t addr;
} HumImpl;

static SensorStatus hum_init(Sensor* self, const SensorConfig* cfg) {
    HumImpl* impl = (HumImpl*)self->_cfg;
    impl->addr = cfg ? cfg->dev_addr : 0x40;
    return SENSOR_OK;
}
static SensorStatus hum_read(Sensor* self, float* out)
{
    (void)self;
    if (out) {
        *out = (float)rand()/(float)RAND_MAX*80.0f;
    }
    return SENSOR_OK;
}
static void hum_deinit(Sensor* self)
{
    free(self->_cfg);
}
static const char* hum_unit(Sensor* self)
{ 
    (void)self;
    return "%RH";
}

static Sensor* hum_create(void) {
    Sensor* sens = (Sensor*)malloc(sizeof(Sensor));
    SensorConfig* cfg = (SensorConfig*)malloc(sizeof(SensorConfig));
    if (!sens || !cfg) {
        free(sens);
        free(cfg);
        return NULL;
    }

    sens->_cfg = cfg;

    sens->init = hum_init;
    sens->read = hum_read;
    sens->deinit = hum_deinit;
    sens->calibrate = NULL;
    sens->unit = hum_unit;
    
    return sens;
}

static const SensorDriver HUM_DRIVER = {
    .kind = "humidity",
    .create = hum_create
};

void humidity_driver_register(void) {
    (void)sensor_register_driver(&HUM_DRIVER);
}
