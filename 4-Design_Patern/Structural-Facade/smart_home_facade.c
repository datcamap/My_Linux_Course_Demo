#include "smart_home_facade.h"
#include <stddef.h> // NULL

static SceneOptions defaults(void) {
    SceneOptions o;
    o.bedroom_brightness = 60;
    o.comfort_temp = 24.0f;
    o.keep_perimeter_armed = 0;
    return o;
}

void facade_init(SmartHomeFacade* f, Lighting* l, Security* s, HVAC* h) {
    f->lighting = l;
    f->security = s;
    f->hvac     = h;
}

void facade_activate_morning_routine(SmartHomeFacade* f, const SceneOptions* opt) {
    SceneOptions o = opt ? *opt : defaults();

    // Security: cameras off indoors; disarm unless keep_perimeter_armed is requested
    security_enable_cameras(f->security, 0);
    if (!o.keep_perimeter_armed) {
        security_disarm(f->security);
    } else {
        security_arm_perimeter(f->security);
    }

    // Lighting: gentle ramp can be handled inside driver; here we just set values
    lighting_set_room_brightness(f->lighting, "Bedroom", o.bedroom_brightness);
    lighting_set_room_brightness(f->lighting, "LivingRoom", 50);

    // HVAC: comfort
    hvac_set_mode(f->hvac, HVAC_AUTO);
    hvac_set_target_temp(f->hvac, o.comfort_temp);
}

void facade_activate_away_mode(SmartHomeFacade* f) {
    lighting_turn_off_all(f->lighting);
    hvac_set_mode(f->hvac, HVAC_OFF);
    security_enable_cameras(f->security, 1);
    security_arm_perimeter(f->security);
}

void facade_set_movie_night_scene(SmartHomeFacade* f) {
    lighting_set_room_brightness(f->lighting, "LivingRoom", 15);
    lighting_set_room_brightness(f->lighting, "Hallway", 5);
    hvac_set_mode(f->hvac, HVAC_AUTO);
    hvac_set_target_temp(f->hvac, 23.0f);
    security_enable_cameras(f->security, 1); // keep perimeter cams
}

void facade_set_room_brightness(SmartHomeFacade* f, const char* room, int pct) {
    lighting_set_room_brightness(f->lighting, room, pct);
}

void facade_set_comfort_temp(SmartHomeFacade* f, float c) {
    hvac_set_mode(f->hvac, HVAC_AUTO);
    hvac_set_target_temp(f->hvac, c);
}
