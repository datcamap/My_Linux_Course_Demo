#include <stdio.h>
#include <string.h>
#include "lighting.h"

typedef struct {
    // pretend Zigbee addr, group id, etc.
    int dummy;
} ZigbeeLightingImpl;

static void zigbee_set_room_brightness(Lighting* self, const char* room, int percent) {
    ZigbeeLightingImpl* impl = (ZigbeeLightingImpl*)self->impl; (void)impl;
    if (percent < 0) {
        percent = 0;
    }
    if (percent > 100) {
        percent = 100;
    }
    printf("[LIGHT] %-12s = %3d%%\n", room ? room : "(null)", percent);
}
static void zigbee_turn_off_all(Lighting* self) {
    ZigbeeLightingImpl* impl = (ZigbeeLightingImpl*)self->impl; (void)impl;
    printf("[LIGHT] off all\n");
}

static const LightingOps ZIGBEE_LIGHTING_OPS = {
    .set_room_brightness = zigbee_set_room_brightness,
    .turn_off_all = zigbee_turn_off_all,
};

void lighting_driver_mock_init(Lighting* obj, ZigbeeLightingImpl* storage) {
    obj->ops = &ZIGBEE_LIGHTING_OPS;
    obj->impl = storage;
    storage->dummy = 0;
}
