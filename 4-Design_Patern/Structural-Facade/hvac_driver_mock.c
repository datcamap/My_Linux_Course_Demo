#include <stdio.h>
#include "hvac.h"

typedef struct {
    float target_c;
    HvacMode mode;
} SimpleHVACImpl;

static void simple_set_target_temp(HVAC* self, float c) {
    SimpleHVACImpl* impl = (SimpleHVACImpl*)self->impl;
    impl->target_c = c;
    printf("[HVAC] target = %.1fC\n", c);
}
static void simple_set_mode(HVAC* self, HvacMode m) {
    SimpleHVACImpl* impl = (SimpleHVACImpl*)self->impl;
    impl->mode = m;
    printf("[HVAC] mode set\n");
}

static const HVACOps SIMPLE_HVAC_OPS = {
    .set_target_temp = simple_set_target_temp,
    .set_mode = simple_set_mode,
};

void hvac_driver_mock_init(HVAC* obj, SimpleHVACImpl* storage) {
    obj->ops = &SIMPLE_HVAC_OPS;
    obj->impl = storage;
    storage->target_c = 24.0f;
    storage->mode = HVAC_OFF;
}
