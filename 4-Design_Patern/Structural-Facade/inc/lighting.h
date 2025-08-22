#ifndef LIGHTING_H
#define LIGHTING_H

#include <stdint.h>

typedef struct Lighting Lighting;

typedef struct {
    void (*set_room_brightness)(Lighting* self, const char* room, int percent); // 0..100
    void (*turn_off_all)(Lighting* self);
} LightingOps;

struct Lighting {
    const LightingOps* ops;
    void* impl; // driver-specific state
};

static inline void lighting_set_room_brightness(Lighting* l, const char* room, int pct) {
    if (l && l->ops && l->ops->set_room_brightness) l->ops->set_room_brightness(l, room, pct);
}
static inline void lighting_turn_off_all(Lighting* l) {
    if (l && l->ops && l->ops->turn_off_all) l->ops->turn_off_all(l);
}

#endif // LIGHTING_H
