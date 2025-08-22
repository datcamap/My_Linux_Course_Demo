#include "smart_home_facade.h"
#include <stddef.h>
#include <stdio.h>

#define DEFAULT_BRIGHTNESS 60
#define DEFAULT_TEMPERATURE 24.0f
#define DEFAULT_PERIMETER 0

static SceneOptions defaults(void)
{
    SceneOptions opts;
    opts.bedroom_brightness = DEFAULT_BRIGHTNESS;
    opts.comfort_temp = DEFAULT_TEMPERATURE;
    opts.keep_perimeter_armed = DEFAULT_PERIMETER;
    return opts;
}

void facade_init(SmartHomeFacade* f, Lighting* l, Security* s, HVAC* h)
{
    f->lighting = l;
    f->security = s;
    f->hvac     = h;
}

void facade_activate_morning_routine(SmartHomeFacade* fcd, const SceneOptions* options)
{
    printf("---Morning-Routine---\n");

    SceneOptions opts = options ? *options : defaults();

    // Security: cameras off indoors; disarm unless keep_perimeter_armed is requested
    security_enable_cameras(fcd->security, 0);
    if (!opts.keep_perimeter_armed) {
        security_disarm(fcd->security);
    } else {
        security_arm_perimeter(fcd->security);
    }

    // Lighting: gentle ramp can be handled inside driver; here we just set values
    lighting_set_room_brightness(fcd->lighting, "Bedroom", opts.bedroom_brightness);
    lighting_set_room_brightness(fcd->lighting, "LivingRoom", 50);

    // HVAC: comfort
    hvac_set_mode(fcd->hvac, HVAC_AUTO);
    hvac_set_target_temp(fcd->hvac, opts.comfort_temp);
}

void facade_activate_away_mode(SmartHomeFacade* fcd)
{
    printf("---Away-Mode---\n");

    lighting_turn_off_all(fcd->lighting);
    hvac_set_mode(fcd->hvac, HVAC_OFF);
    security_enable_cameras(fcd->security, 1);
    security_arm_perimeter(fcd->security);
}

void facade_set_movie_night_scene(SmartHomeFacade* fcd)
{
    printf("---Movie-Night-Scene---\n");

    lighting_set_room_brightness(fcd->lighting, "LivingRoom", 15);
    lighting_set_room_brightness(fcd->lighting, "Hallway", 5);
    hvac_set_mode(fcd->hvac, HVAC_AUTO);
    hvac_set_target_temp(fcd->hvac, 23.0f);
    security_enable_cameras(fcd->security, 1); 
}

void facade_set_room_brightness(SmartHomeFacade* fcd, const char* room, int pct)
{
    lighting_set_room_brightness(fcd->lighting, room, pct);
}

void facade_set_comfort_temp(SmartHomeFacade* fcd, float celcius)
{
    hvac_set_mode(fcd->hvac, HVAC_AUTO);
    hvac_set_target_temp(fcd->hvac, celcius);
}
