#include <stdio.h>
#include "security.h"

typedef struct {
    int perimeter_armed;
    int cameras_on;
} BasicSecurityImpl;

static void basic_arm_perimeter(Security* self) {
    BasicSecurityImpl* impl = (BasicSecurityImpl*)self->impl;
    impl->perimeter_armed = 1;
    printf("[SEC ] arm perimeter\n");
}
static void basic_disarm(Security* self) {
    BasicSecurityImpl* impl = (BasicSecurityImpl*)self->impl;
    impl->perimeter_armed = 0;
    printf("[SEC ] disarm\n");
}
static void basic_enable_cameras(Security* self, int on) {
    BasicSecurityImpl* impl = (BasicSecurityImpl*)self->impl;
    impl->cameras_on = !!on;
    printf("[SEC ] cameras %s\n", impl->cameras_on ? "on" : "off");
}

static const SecurityOps BASIC_SECURITY_OPS = {
    .arm_perimeter = basic_arm_perimeter,
    .disarm = basic_disarm,
    .enable_cameras = basic_enable_cameras,
};

void security_driver_mock_init(Security* obj, BasicSecurityImpl* storage) {
    obj->ops = &BASIC_SECURITY_OPS;
    obj->impl = storage;
    storage->perimeter_armed = 0;
    storage->cameras_on = 0;
}
